const bgfx = require('../index');
const VertexDeclaration = require('../VertexDeclaration');

const specNum = [
  { attr: bgfx.POSITION, type: bgfx.FLOAT, count: 3 },
  { attr: bgfx.COLOR_0, type: bgfx.UINT_8, count: 4 }
];

const specStr = [
  { attr: 'POSITION', type: 'FLOAT', count: 3 },
  { attr: 'COLOR_0', type: 'UINT_8', count: 4 }
];

const specInvalid1 = [
  { attr: 'BANANA', type: 'FLOAT', count: 3 },
  { attr: 'COLOR_0', type: 'UINT_8', count: 4 }
];

const specInvalid2 = [
  { attr: 'POSITION', type: 'FLOAT', count: 3 },
  { attr: 'COLOR_0', type: 'BANANA', count: 4 }
];

const buffer1 = {
  [bgfx.POSITION]: [
    [-1.0, 1.0, 1.0],
    [1.0, 1.0, 1.0],
    [-1.0, -1.0, 1.0],
    [1.0, -1.0, 1.0],
    [-1.0, 1.0, -1.0],
    [1.0, 1.0, -1.0],
    [-1.0, -1.0, -1.0],
    [1.0, -1.0, -1.0]
  ],
  [bgfx.COLOR_0]: [
    0xff000000,
    0xff0000ff,
    0xff00ff00,
    0xff00ffff,
    0xffff0000,
    0xffff00ff,
    0xffffff00,
    0xffffffff
  ]
};

const buffer2 = {
  POSITION: [
    [-1.0, 1.0, 1.0],
    [1.0, 1.0, 1.0],
    [-1.0, -1.0, 1.0],
    [1.0, -1.0, 1.0],
    [-1.0, 1.0, -1.0],
    [1.0, 1.0, -1.0],
    [-1.0, -1.0, -1.0],
    [1.0, -1.0, -1.0]
  ],
  COLOR_0: [
    0xff000000,
    0xff0000ff,
    0xff00ff00,
    0xff00ffff,
    0xffff0000,
    0xffff00ff,
    0xffffff00,
    0xffffffff
  ]
};

const buffer3 = {
  POSITION: [
    [-1.0, 1.0, 1.0],
    [1.0, 1.0, 1.0],
    [-1.0, -1.0, 1.0],
    [1.0, -1.0, 1.0],
    [-1.0, 1.0, -1.0],
    [1.0, 1.0, -1.0],
    [-1.0, -1.0, -1.0],
    [1.0, -1.0, -1.0]
  ],
  COLOR_0: [
    [0xff, 0x00, 0x00, 0x00],
    [0xff, 0x00, 0x00, 0xff],
    [0xff, 0x00, 0xff, 0x00],
    [0xff, 0x00, 0xff, 0xff],
    [0xff, 0xff, 0x00, 0x00],
    [0xff, 0xff, 0x00, 0xff],
    [0xff, 0xff, 0xff, 0x00],
    [0xff, 0xff, 0xff, 0xff]
  ]
};

describe('VertexDeclaration', () => {
  describe('#constructor', () => {
    it('handles enum spec', () => {
      fail();
    });

    it('handles string spec', () => {
      fail();
    });

    it('rejects invalid attribute', () => {
      fail();
    });

    it('rejects invalid type', () => {
      fail();
    });
  });

  it('#allocate', () => {
    fail();
  });

  describe('#fromData', () => {
    it('handles enum spec', () => {
      fail();
    });

    it('handles string spec', () => {
      fail();
    });

    it('handles multiple defaults', () => {
      fail();
    });
  });
});
