exports.spec = [
  { attr: 'POSITION', type: 'FLOAT', count: 3 },
  { attr: 'COLOR_0', type: 'UINT_8', count: 4 },
];

exports.specInvalidAttr = [
  { attr: 'BANANA', type: 'FLOAT', count: 3 },
  { attr: 'COLOR_0', type: 'UINT_8', count: 4 },
];

exports.specInvalidType = [
  { attr: 'POSITION', type: 'FLOAT', count: 3 },
  { attr: 'COLOR_0', type: 'BANANA', count: 4 },
];

exports.buffer = {
  POSITION: [
    [-1.0, 1.0, 1.0],
    [1.0, 1.0, 1.0],
    [-1.0, -1.0, 1.0],
    [1.0, -1.0, 1.0],
    [-1.0, 1.0, -1.0],
    [1.0, 1.0, -1.0],
    [-1.0, -1.0, -1.0],
    [1.0, -1.0, -1.0],
  ],
  COLOR_0: [
    [0xff, 0x00, 0x00, 0x00],
    [0xff, 0x00, 0x00, 0xff],
    [0xff, 0x00, 0xff, 0x00],
    [0xff, 0x00, 0xff, 0xff],
    [0xff, 0xff, 0x00, 0x00],
    [0xff, 0xff, 0x00, 0xff],
    [0xff, 0xff, 0xff, 0x00],
    [0xff, 0xff, 0xff, 0xff],
  ],
};
