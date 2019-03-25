const bgfx = require('../index');

describe('bgfx', () => {
  it('imports successfully', () => {
    expect(bgfx).toBeDefined();
  });

  it('includes enums', () => {
    expect(bgfx.FATAL).toMatchObject({
      DEBUG_CHECK: 0,
      INVALID_SHADER: 1,
      UNABLE_TO_INITIALIZE: 2,
      UNABLE_TO_CREATE_TEXTURE: 3,
      DEVICE_LOST: 4
    });
  });

  // TODO: add unit tests per function.
});
