const { checksumFile, sleep } = require('../../lib/utils');
const path = require('path');

const testPath = path.resolve(__dirname, 'payload.txt');

describe('checksumFile', () => {
  it('computes md5 hashes correctly', async () => {
    const md5 = await checksumFile(testPath, 'md5');
    expect(md5).toEqual('851f29eb40bc9f8367f4d43759f87f79');
  });
});

describe('sleep', () => {
  const delayMs = 100;

  it('terminates if given no arguments', async () => {
    await sleep();
  }, 10);

  it(
    'waits the right amount of time',
    async () => {
      const start = process.hrtime.bigint();
      await sleep(delayMs);
      const end = process.hrtime.bigint();
      expect(Number(end - start)).toBeGreaterThan(delayMs);
    },
    delayMs + 10,
  );
});
