const crypto = require('crypto');
const fs = require('fs');

/**
 * Compute the hash of a file on disk.
 *
 * @param {str} path the path to the file
 * @param {str} hashType optional type of hash to compute (default: md5)
 */
exports.checksumFile = async (path, hashType) => {
  const hash = crypto.createHash(hashType || 'md5');
  const stream = fs.createReadStream(path);

  const result = await new Promise((resolve, reject) => {
    stream.on('data', chunk => hash.update(chunk));
    stream.on('end', () => resolve(hash.digest('hex')));
    stream.on('error', err => reject(err));
  });

  stream.pipe(hash);
  return result;
};

/**
 * Sleep for a specified amount of time.
 * Returns a promise that will block until the time has passed.
 *
 * @param {Number} ms the number of milliseconds to sleep.
 */
exports.sleep = (ms = 0) => new Promise(r => setTimeout(r, ms));
