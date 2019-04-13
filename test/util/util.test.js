const util = require('../../lib/util');
const path = require('path');

const testPath = path.resolve(__dirname, 'test_payload.txt');

describe('checksumFile', () => {
  it('computes md5 hashes correctly', async () => {
    const md5 = await util.checksumFile(testPath, 'md5');
    expect(md5).toEqual('04c79b9810a0b59aa9b5365c25782505');
  });
});
