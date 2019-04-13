const { checksumFile } = require('../../lib/utils');
const path = require('path');

const testPath = path.resolve(__dirname, 'payload.txt');

describe('checksumFile', () => {
  it('computes md5 hashes correctly', async () => {
    const md5 = await checksumFile(testPath, 'md5');
    expect(md5).toEqual('851f29eb40bc9f8367f4d43759f87f79');
  });
});
