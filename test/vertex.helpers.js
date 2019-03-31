const bgfx = require('../index');

const { POSITION, COLOR_0 } = bgfx.ATTRIB;
const { FLOAT, UINT_8 } = bgfx.ATTRIB_TYPE;

exports.specEnum = [
  { attr: POSITION, type: FLOAT, count: 3 },
  { attr: COLOR_0, type: UINT_8, count: 4 }
];

exports.specStr = [
  { attr: 'POSITION', type: 'FLOAT', count: 3 },
  { attr: 'COLOR_0', type: 'UINT_8', count: 4 }
];

exports.specInvalidAttr = [
  { attr: 'BANANA', type: 'FLOAT', count: 3 },
  { attr: 'COLOR_0', type: 'UINT_8', count: 4 }
];

exports.specInvalidType = [
  { attr: 'POSITION', type: 'FLOAT', count: 3 },
  { attr: 'COLOR_0', type: 'BANANA', count: 4 }
];

exports.bufferEnum = {
  [POSITION]: [
    [-1.0, 1.0, 1.0],
    [1.0, 1.0, 1.0],
    [-1.0, -1.0, 1.0],
    [1.0, -1.0, 1.0],
    [-1.0, 1.0, -1.0],
    [1.0, 1.0, -1.0],
    [-1.0, -1.0, -1.0],
    [1.0, -1.0, -1.0]
  ],
  [COLOR_0]: [
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

exports.bufferStr = {
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
