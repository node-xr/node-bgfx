// Autogenerated -- DO NOT EDIT

exports.FATAL = {
  DEBUG_CHECK         :  0,
  INVALID_SHADER      :  1,
  UNABLE_TO_INITIALIZE:  2,
  UNABLE_TO_CREATE_TEXTURE:  3,
  DEVICE_LOST         :  4 
}

exports.RENDERER_TYPE = {
  NOOP                :  0,
  DIRECT_3D9          :  1,
  DIRECT_3D11         :  2,
  DIRECT_3D12         :  3,
  GNM                 :  4,
  METAL               :  5,
  NVN                 :  6,
  OPEN_GLES           :  7,
  OPEN_GL             :  8,
  VULKAN              :  9 
}

exports.ACCESS = {
  READ                :  0,
  WRITE               :  1,
  READ_WRITE          :  2 
}

exports.ATTRIB = {
  POSITION            :  0,
  NORMAL              :  1,
  TANGENT             :  2,
  BITANGENT           :  3,
  COLOR_0             :  4,
  COLOR_1             :  5,
  COLOR_2             :  6,
  COLOR_3             :  7,
  INDICES             :  8,
  WEIGHT              :  9,
  TEX_COORD_0         : 10,
  TEX_COORD_1         : 11,
  TEX_COORD_2         : 12,
  TEX_COORD_3         : 13,
  TEX_COORD_4         : 14,
  TEX_COORD_5         : 15,
  TEX_COORD_6         : 16,
  TEX_COORD_7         : 17 
}

exports.ATTRIB_TYPE = {
  UINT_8              :  0,
  UINT_10             :  1,
  INT_16              :  2,
  HALF                :  3,
  FLOAT               :  4 
}

exports.TEXTURE_FORMAT = {
  BC1                 :  0,
  BC2                 :  1,
  BC3                 :  2,
  BC4                 :  3,
  BC5                 :  4,
  BC6H                :  5,
  BC7                 :  6,
  ETC1                :  7,
  ETC2                :  8,
  ETC2A               :  9,
  ETC2A1              : 10,
  PTC12               : 11,
  PTC14               : 12,
  PTC12A              : 13,
  PTC14A              : 14,
  PTC22               : 15,
  PTC24               : 16,
  ATC                 : 17,
  ATCE                : 18,
  ATCI                : 19,
  ASTC4X_4            : 20,
  ASTC5X_5            : 21,
  ASTC6X_6            : 22,
  ASTC8X_5            : 23,
  ASTC8X_6            : 24,
  ASTC10X_5           : 25,
  UNKNOWN             : 26,
  R1                  : 27,
  A8                  : 28,
  R8                  : 29,
  R8I                 : 30,
  R8U                 : 31,
  R8S                 : 32,
  R16                 : 33,
  R16I                : 34,
  R16U                : 35,
  R16F                : 36,
  R16S                : 37,
  R32I                : 38,
  R32U                : 39,
  R32F                : 40,
  RG8                 : 41,
  RG8I                : 42,
  RG8U                : 43,
  RG8S                : 44,
  RG16                : 45,
  RG16I               : 46,
  RG16U               : 47,
  RG16F               : 48,
  RG16S               : 49,
  RG32I               : 50,
  RG32U               : 51,
  RG32F               : 52,
  RGB8                : 53,
  RGB8I               : 54,
  RGB8U               : 55,
  RGB8S               : 56,
  RGB9E5F             : 57,
  BGRA8               : 58,
  RGBA8               : 59,
  RGBA8I              : 60,
  RGBA8U              : 61,
  RGBA8S              : 62,
  RGBA16              : 63,
  RGBA16I             : 64,
  RGBA16U             : 65,
  RGBA16F             : 66,
  RGBA16S             : 67,
  RGBA32I             : 68,
  RGBA32U             : 69,
  RGBA32F             : 70,
  R5G6B5              : 71,
  RGBA4               : 72,
  RGB5A1              : 73,
  RGB10A2             : 74,
  RG11B10F            : 75,
  UNKNOWN_DEPTH       : 76,
  D16                 : 77,
  D24                 : 78,
  D24S8               : 79,
  D32                 : 80,
  D16F                : 81,
  D24F                : 82,
  D32F                : 83,
  D0S8                : 84 
}

exports.UNIFORM_TYPE = {
  SAMPLER             :  0, // Sampler.
  END                 :  1, // Reserved, do not use.
  VEC_4               :  2, // 4 floats vector.
  MAT_3               :  3, // 3x3 matrix.
  MAT_4               :  4  // 4x4 matrix.
}

exports.BACKBUFFER_RATIO = {
  EQUAL               :  0, // Equal to backbuffer.
  HALF                :  1, // One half size of backbuffer.
  QUARTER             :  2, // One quarter size of backbuffer.
  EIGHTH              :  3, // One eighth size of backbuffer.
  SIXTEENTH           :  4, // One sixteenth size of backbuffer.
  DOUBLE              :  5  // Double size of backbuffer.
}

exports.OCCLUSION_QUERY_RESULT = {
  INVISIBLE           :  0, // Query failed test.
  VISIBLE             :  1, // Query passed test.
  NO_RESULT           :  2  // Query result is not available yet.
}

exports.TOPOLOGY = {
  TRI_LIST            :  0, // Triangle list.
  TRI_STRIP           :  1, // Triangle strip.
  LINE_LIST           :  2, // Line list.
  LINE_STRIP          :  3, // Line strip.
  POINT_LIST          :  4  // Point list.
}

exports.TOPOLOGY_CONVERT = {
  TRI_LIST_FLIP_WINDING:  0, // Flip winding order of triangle list.
  TRI_STRIP_FLIP_WINDING:  1, // Flip winding order of trinagle strip.
  TRI_LIST_TO_LINE_LIST:  2, // Convert triangle list to line list.
  TRI_STRIP_TO_TRI_LIST:  3, // Convert triangle strip to triangle list.
  LINE_STRIP_TO_LINE_LIST:  4  // Convert line strip to line list.
}

exports.TOPOLOGY_SORT = {
  DIRECTION_FRONT_TO_BACK_MIN:  0,
  DIRECTION_FRONT_TO_BACK_AVG:  1,
  DIRECTION_FRONT_TO_BACK_MAX:  2,
  DIRECTION_BACK_TO_FRONT_MIN:  3,
  DIRECTION_BACK_TO_FRONT_AVG:  4,
  DIRECTION_BACK_TO_FRONT_MAX:  5,
  DISTANCE_FRONT_TO_BACK_MIN:  6,
  DISTANCE_FRONT_TO_BACK_AVG:  7,
  DISTANCE_FRONT_TO_BACK_MAX:  8,
  DISTANCE_BACK_TO_FRONT_MIN:  9,
  DISTANCE_BACK_TO_FRONT_AVG: 10,
  DISTANCE_BACK_TO_FRONT_MAX: 11 
}

exports.VIEW_MODE = {
  DEFAULT             :  0, // Default sort order.
  SEQUENTIAL          :  1, // Sort in the same order in which submit calls were called.
  DEPTH_ASCENDING     :  2, // Sort draw call depth in ascending order.
  DEPTH_DESCENDING    :  3  // Sort draw call depth in descending order.
}

exports.RENDER_FRAME = {
  NO_CONTEXT          :  0,
  RENDER              :  1,
  TIMEOUT             :  2,
  EXITING             :  3 
}
