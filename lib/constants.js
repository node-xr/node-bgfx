exports.API_VERSION = 98;
exports.INVALID_HANDLE = 65535;

/// Color RGB/alpha/depth write. When it's not specified write will be disabled.
exports.STATE_WRITE_R = BigInt(0x0000000000000001); //!< Enable R write.
exports.STATE_WRITE_G = BigInt(0x0000000000000002); //!< Enable G write.
exports.STATE_WRITE_B = BigInt(0x0000000000000004); //!< Enable B write.
exports.STATE_WRITE_A = BigInt(0x0000000000000008); //!< Enable alpha write.
exports.STATE_WRITE_Z = BigInt(0x0000004000000000); //!< Enable depth write.

/// Enable RGB write.
exports.STATE_WRITE_RGB =
  exports.STATE_WRITE_R | exports.STATE_WRITE_G | exports.STATE_WRITE_B;

/// Write all channels mask.
exports.STATE_WRITE_MASK =
  exports.STATE_WRITE_RGB | exports.STATE_WRITE_A | exports.STATE_WRITE_Z;

/// Depth test state. When `BGFX_STATE_DEPTH_` is not specified depth test will be disabled.
exports.STATE_DEPTH_TEST_LESS = BigInt(0x0000000000000010); //!< Enable depth test, less.
exports.STATE_DEPTH_TEST_LEQUAL = BigInt(0x0000000000000020); //!< Enable depth test, less or equal.
exports.STATE_DEPTH_TEST_EQUAL = BigInt(0x0000000000000030); //!< Enable depth test, equal.
exports.STATE_DEPTH_TEST_GEQUAL = BigInt(0x0000000000000040); //!< Enable depth test, greater or equal.
exports.STATE_DEPTH_TEST_GREATER = BigInt(0x0000000000000050); //!< Enable depth test, greater.
exports.STATE_DEPTH_TEST_NOTEQUAL = BigInt(0x0000000000000060); //!< Enable depth test, not equal.
exports.STATE_DEPTH_TEST_NEVER = BigInt(0x0000000000000070); //!< Enable depth test, never.
exports.STATE_DEPTH_TEST_ALWAYS = BigInt(0x0000000000000080); //!< Enable depth test, always.
exports.STATE_DEPTH_TEST_SHIFT = 4; //!< Depth test state bit shift.
exports.STATE_DEPTH_TEST_MASK = BigInt(0x00000000000000f0); //!< Depth test state bit mask.

/// Use BGFX_STATE_BLEND_FUNC(_src, _dst) or BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)
/// helper macros.
exports.STATE_BLEND_ZERO = BigInt(0x0000000000001000); //!< 0, 0, 0, 0
exports.STATE_BLEND_ONE = BigInt(0x0000000000002000); //!< 1, 1, 1, 1
exports.STATE_BLEND_SRC_COLOR = BigInt(0x0000000000003000); //!< Rs, Gs, Bs, As
exports.STATE_BLEND_INV_SRC_COLOR = BigInt(0x0000000000004000); //!< 1-Rs, 1-Gs, 1-Bs, 1-As
exports.STATE_BLEND_SRC_ALPHA = BigInt(0x0000000000005000); //!< As, As, As, As
exports.STATE_BLEND_INV_SRC_ALPHA = BigInt(0x0000000000006000); //!< 1-As, 1-As, 1-As, 1-As
exports.STATE_BLEND_DST_ALPHA = BigInt(0x0000000000007000); //!< Ad, Ad, Ad, Ad
exports.STATE_BLEND_INV_DST_ALPHA = BigInt(0x0000000000008000); //!< 1-Ad, 1-Ad, 1-Ad ,1-Ad
exports.STATE_BLEND_DST_COLOR = BigInt(0x0000000000009000); //!< Rd, Gd, Bd, Ad
exports.STATE_BLEND_INV_DST_COLOR = BigInt(0x000000000000a000); //!< 1-Rd, 1-Gd, 1-Bd, 1-Ad
exports.STATE_BLEND_SRC_ALPHA_SAT = BigInt(0x000000000000b000); //!< f, f, f, 1; f = min(As, 1-Ad)
exports.STATE_BLEND_FACTOR = BigInt(0x000000000000c000); //!< Blend factor
exports.STATE_BLEND_INV_FACTOR = BigInt(0x000000000000d000); //!< 1-Blend factor
exports.STATE_BLEND_SHIFT = 12; //!< Blend state bit shift.
exports.STATE_BLEND_MASK = BigInt(0x000000000ffff000); //!< Blend state bit mask.

/// Use BGFX_STATE_BLEND_EQUATION(_equation) or BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)
/// helper macros.
exports.STATE_BLEND_EQUATION_ADD = BigInt(0x0000000000000000); //!< Blend add: src + dst.
exports.STATE_BLEND_EQUATION_SUB = BigInt(0x0000000010000000); //!< Blend subtract: src - dst.
exports.STATE_BLEND_EQUATION_REVSUB = BigInt(0x0000000020000000); //!< Blend reverse subtract: dst - src.
exports.STATE_BLEND_EQUATION_MIN = BigInt(0x0000000030000000); //!< Blend min: min(src, dst).
exports.STATE_BLEND_EQUATION_MAX = BigInt(0x0000000040000000); //!< Blend max: max(src, dst).
exports.STATE_BLEND_EQUATION_SHIFT = 28; //!< Blend equation bit shift.
exports.STATE_BLEND_EQUATION_MASK = BigInt(0x00000003f0000000); //!< Blend equation bit mask.

exports.STATE_BLEND_INDEPENDENT = BigInt(0x0000000400000000); //!< Enable blend independent.
exports.STATE_BLEND_ALPHA_TO_COVERAGE = BigInt(0x0000000800000000); //!< Enable alpha to coverage.

/// Cull state. When `BGFX_STATE_CULL_*` is not specified culling will be disabled.
exports.STATE_CULL_CW = BigInt(0x0000001000000000); //!< Cull clockwise triangles.
exports.STATE_CULL_CCW = BigInt(0x0000002000000000); //!< Cull counter-clockwise triangles.
exports.STATE_CULL_SHIFT = 36; //!< Culling mode bit shift.
exports.STATE_CULL_MASK = BigInt(0x0000003000000000); //!< Culling mode bit mask.

/// See BGFX_STATE_ALPHA_REF(_ref) helper macro.
exports.STATE_ALPHA_REF_SHIFT = 40; //!< Alpha reference bit shift.
exports.STATE_ALPHA_REF_MASK = BigInt(0x0000ff0000000000); //!< Alpha reference bit mask.

exports.STATE_PT_TRISTRIP = BigInt(0x0001000000000000); //!< Tristrip.
exports.STATE_PT_LINES = BigInt(0x0002000000000000); //!< Lines.
exports.STATE_PT_LINESTRIP = BigInt(0x0003000000000000); //!< Line strip.
exports.STATE_PT_POINTS = BigInt(0x0004000000000000); //!< Points.
exports.STATE_PT_SHIFT = 48; //!< Primitive type bit shift.
exports.STATE_PT_MASK = BigInt(0x0007000000000000); //!< Primitive type bit mask.

/// See BGFX_STATE_POINT_SIZE(_size) helper macro.
exports.STATE_POINT_SIZE_SHIFT = 52; //!< Point size bit shift.
exports.STATE_POINT_SIZE_MASK = BigInt(0x00f0000000000000); //!< Point size bit mask.

/// Enable MSAA write when writing into MSAA frame buffer.
/// This flag is ignored when not writing into MSAA frame buffer.
exports.STATE_MSAA = BigInt(BigInt(0x0100000000000000)); //!< Enable MSAA rasterization.
exports.STATE_LINEAA = BigInt(0x0200000000000000); //!< Enable line AA rasterization.
exports.STATE_CONSERVATIVE_RASTER = BigInt(0x0400000000000000); //!< Enable conservative rasterization.

/// Do not use!
exports.STATE_RESERVED_SHIFT = 61; //!< Internal bits shift.
exports.STATE_RESERVED_MASK = BigInt(0xe000000000000000); //!< Internal bits mask.

///
exports.STATE_NONE = BigInt(0x0000000000000000); //!< No state.
exports.STATE_MASK = BigInt(0xffffffffffffffff); //!< State mask.

/// Default state is write to RGB, alpha, and depth with depth test less enabled, with clockwise
/// culling and MSAA (when writing into MSAA frame buffer, otherwise this flag is ignored).
exports.STATE_DEFAULT =
  exports.STATE_WRITE_RGB |
  exports.STATE_WRITE_A |
  exports.STATE_WRITE_Z |
  exports.STATE_DEPTH_TEST_LESS |
  exports.STATE_CULL_CW |
  exports.STATE_MSAA;

/// Alpha reference value.
exports.STATE_ALPHA_REF = _ref =>
  (_ref << exports.STATE_ALPHA_REF_SHIFT) & exports.STATE_ALPHA_REF_MASK;

/// Point size value.
exports.STATE_POINT_SIZE = _size =>
  (_size << exports.STATE_POINT_SIZE_SHIFT) & exports.STATE_POINT_SIZE_MASK;

/// Blend function separate.
exports.STATE_BLEND_FUNC_SEPARATE = (_srcRGB, _dstRGB, _srcA, _dstA) =>
  _srcRGB | (_dstRGB << 4n) | ((_srcA | (_dstA << 4n)) << 8n);

/// Blend equation separate.
exports.STATE_BLEND_EQUATION_SEPARATE = (_equationRGB, _equationA) =>
  _equationRGB | (_equationA << 3n);

/// Blend function.
exports.STATE_BLEND_FUNC = (_src, _dst) =>
  exports.STATE_BLEND_FUNC_SEPARATE(_src, _dst, _src, _dst);

/// Blend equation.
exports.STATE_BLEND_EQUATION = _equation =>
  exports.STATE_BLEND_EQUATION_SEPARATE(_equation, _equation);

/// Utility predefined blend modes.

/// Additive blending.
exports.STATE_BLEND_ADD = exports.STATE_BLEND_FUNC(
  exports.STATE_BLEND_ONE,
  exports.STATE_BLEND_ONE,
);

/// Alpha blend.
exports.STATE_BLEND_ALPHA = exports.STATE_BLEND_FUNC(
  exports.STATE_BLEND_SRC_ALPHA,
  exports.STATE_BLEND_INV_SRC_ALPHA,
);

/// Selects darker color of blend.
exports.STATE_BLEND_DARKEN =
  exports.STATE_BLEND_FUNC(exports.STATE_BLEND_ONE, exports.STATE_BLEND_ONE) |
  exports.STATE_BLEND_EQUATION(exports.STATE_BLEND_EQUATION_MIN);

/// Selects lighter color of blend.
exports.STATE_BLEND_LIGHTEN =
  exports.STATE_BLEND_FUNC(exports.STATE_BLEND_ONE, exports.STATE_BLEND_ONE) |
  exports.STATE_BLEND_EQUATION(exports.STATE_BLEND_EQUATION_MAX);

/// Multiplies colors.
exports.STATE_BLEND_MULTIPLY = exports.STATE_BLEND_FUNC(
  exports.STATE_BLEND_DST_COLOR,
  exports.STATE_BLEND_ZERO,
);

/// Opaque pixels will cover the pixels directly below them without any math or algorithm applied to them.
exports.STATE_BLEND_NORMAL = exports.STATE_BLEND_FUNC(
  exports.STATE_BLEND_ONE,
  exports.STATE_BLEND_INV_SRC_ALPHA,
);

/// Multiplies the inverse of the blend and base colors.
exports.STATE_BLEND_SCREEN = exports.STATE_BLEND_FUNC(
  exports.STATE_BLEND_ONE,
  exports.STATE_BLEND_INV_SRC_COLOR,
);

/// Decreases the brightness of the base color based on the value of the blend color.
exports.STATE_BLEND_LINEAR_BURN =
  exports.STATE_BLEND_FUNC(
    exports.STATE_BLEND_DST_COLOR,
    exports.STATE_BLEND_INV_DST_COLOR,
  ) | exports.STATE_BLEND_EQUATION(exports.STATE_BLEND_EQUATION_SUB);

///
exports.STATE_BLEND_FUNC_RT_x = (_src, _dst) =>
  uint32_t(_src >> exports.STATE_BLEND_SHIFT) |
  (uint32_t(_dst >> exports.STATE_BLEND_SHIFT) << 4);

///
exports.STATE_BLEND_FUNC_RT_xE = (_src, _dst, _equation) =>
  exports.STATE_BLEND_FUNC_RT_x(_src, _dst) |
  (uint32_t(_equation >> exports.STATE_BLEND_EQUATION_SHIFT) << 8);

exports.STATE_BLEND_FUNC_RT_1 = (_src, _dst) =>
  exports.STATE_BLEND_FUNC_RT_x(_src, _dst) << 0;
exports.STATE_BLEND_FUNC_RT_2 = (_src, _dst) =>
  exports.STATE_BLEND_FUNC_RT_x(_src, _dst) << 11;
exports.STATE_BLEND_FUNC_RT_3 = (_src, _dst) =>
  exports.STATE_BLEND_FUNC_RT_x(_src, _dst) << 22;

exports.STATE_BLEND_FUNC_RT_1E = (_src, _dst, _equation) =>
  exports.STATE_BLEND_FUNC_RT_xE(_src, _dst, _equation) << 0;
exports.STATE_BLEND_FUNC_RT_2E = (_src, _dst, _equation) =>
  exports.STATE_BLEND_FUNC_RT_xE(_src, _dst, _equation) << 11;
exports.STATE_BLEND_FUNC_RT_3E = (_src, _dst, _equation) =>
  exports.STATE_BLEND_FUNC_RT_xE(_src, _dst, _equation) << 22;

///
exports.STENCIL_FUNC_REF_SHIFT = 0; //!<
exports.STENCIL_FUNC_REF_MASK = 0x000000ff; //!<
exports.STENCIL_FUNC_RMASK_SHIFT = 8; //!<
exports.STENCIL_FUNC_RMASK_MASK = 0x0000ff00; //!<

///
exports.STENCIL_TEST_LESS = 0x00010000; //!< Enable stencil test, less.
exports.STENCIL_TEST_LEQUAL = 0x00020000; //!< Enable stencil test, less or equal.
exports.STENCIL_TEST_EQUAL = 0x00030000; //!< Enable stencil test, equal.
exports.STENCIL_TEST_GEQUAL = 0x00040000; //!< Enable stencil test, greater or equal.
exports.STENCIL_TEST_GREATER = 0x00050000; //!< Enable stencil test, greater.
exports.STENCIL_TEST_NOTEQUAL = 0x00060000; //!< Enable stencil test, not equal.
exports.STENCIL_TEST_NEVER = 0x00070000; //!< Enable stencil test, never.
exports.STENCIL_TEST_ALWAYS = 0x00080000; //!< Enable stencil test, always.
exports.STENCIL_TEST_SHIFT = 16; //!< Stencil test bit shift.
exports.STENCIL_TEST_MASK = 0x000f0000; //!< Stencil test bit mask.

///
exports.STENCIL_OP_FAIL_S_ZERO = 0x00000000; //!< Zero.
exports.STENCIL_OP_FAIL_S_KEEP = 0x00100000; //!< Keep.
exports.STENCIL_OP_FAIL_S_REPLACE = 0x00200000; //!< Replace.
exports.STENCIL_OP_FAIL_S_INCR = 0x00300000; //!< Increment and wrap.
exports.STENCIL_OP_FAIL_S_INCRSAT = 0x00400000; //!< Increment and clamp.
exports.STENCIL_OP_FAIL_S_DECR = 0x00500000; //!< Decrement and wrap.
exports.STENCIL_OP_FAIL_S_DECRSAT = 0x00600000; //!< Decrement and clamp.
exports.STENCIL_OP_FAIL_S_INVERT = 0x00700000; //!< Invert.
exports.STENCIL_OP_FAIL_S_SHIFT = 20; //!< Stencil operation fail bit shift.
exports.STENCIL_OP_FAIL_S_MASK = 0x00f00000; //!< Stencil operation fail bit mask.

///
exports.STENCIL_OP_FAIL_Z_ZERO = 0x00000000; //!< Zero.
exports.STENCIL_OP_FAIL_Z_KEEP = 0x01000000; //!< Keep.
exports.STENCIL_OP_FAIL_Z_REPLACE = 0x02000000; //!< Replace.
exports.STENCIL_OP_FAIL_Z_INCR = 0x03000000; //!< Increment and wrap.
exports.STENCIL_OP_FAIL_Z_INCRSAT = 0x04000000; //!< Increment and clamp.
exports.STENCIL_OP_FAIL_Z_DECR = 0x05000000; //!< Decrement and wrap.
exports.STENCIL_OP_FAIL_Z_DECRSAT = 0x06000000; //!< Decrement and clamp.
exports.STENCIL_OP_FAIL_Z_INVERT = 0x07000000; //!< Invert.
exports.STENCIL_OP_FAIL_Z_SHIFT = 24; //!< Stencil operation depth fail bit shift
exports.STENCIL_OP_FAIL_Z_MASK = 0x0f000000; //!< Stencil operation depth fail bit mask.

///
exports.STENCIL_OP_PASS_Z_ZERO = 0x00000000; //!< Zero.
exports.STENCIL_OP_PASS_Z_KEEP = 0x10000000; //!< Keep.
exports.STENCIL_OP_PASS_Z_REPLACE = 0x20000000; //!< Replace.
exports.STENCIL_OP_PASS_Z_INCR = 0x30000000; //!< Increment and wrap.
exports.STENCIL_OP_PASS_Z_INCRSAT = 0x40000000; //!< Increment and clamp.
exports.STENCIL_OP_PASS_Z_DECR = 0x50000000; //!< Decrement and wrap.
exports.STENCIL_OP_PASS_Z_DECRSAT = 0x60000000; //!< Decrement and clamp.
exports.STENCIL_OP_PASS_Z_INVERT = 0x70000000; //!< Invert.
exports.STENCIL_OP_PASS_Z_SHIFT = 28; //!< Stencil operation depth pass bit shift
exports.STENCIL_OP_PASS_Z_MASK = 0xf0000000; //!< Stencil operation depth pass bit mask.

///
exports.STENCIL_NONE = 0x00000000; //!<
exports.STENCIL_MASK = 0xffffffff; //!<
exports.STENCIL_DEFAULT = 0x00000000; //!<

/// Set stencil ref value.
exports.STENCIL_FUNC_REF = _ref =>
  (uint32_t(_ref) << exports.STENCIL_FUNC_REF_SHIFT) &
  exports.STENCIL_FUNC_REF_MASK;

/// Set stencil rmask value.
exports.STENCIL_FUNC_RMASK = _mask =>
  (uint32_t(_mask) << exports.STENCIL_FUNC_RMASK_SHIFT) &
  exports.STENCIL_FUNC_RMASK_MASK;

///
exports.CLEAR_NONE = 0x0000; //!< No clear flags.
exports.CLEAR_COLOR = 0x0001; //!< Clear color.
exports.CLEAR_DEPTH = 0x0002; //!< Clear depth.
exports.CLEAR_STENCIL = 0x0004; //!< Clear stencil.
exports.CLEAR_DISCARD_COLOR_0 = 0x0008; //!< Discard frame buffer attachment 0.
exports.CLEAR_DISCARD_COLOR_1 = 0x0010; //!< Discard frame buffer attachment 1.
exports.CLEAR_DISCARD_COLOR_2 = 0x0020; //!< Discard frame buffer attachment 2.
exports.CLEAR_DISCARD_COLOR_3 = 0x0040; //!< Discard frame buffer attachment 3.
exports.CLEAR_DISCARD_COLOR_4 = 0x0080; //!< Discard frame buffer attachment 4.
exports.CLEAR_DISCARD_COLOR_5 = 0x0100; //!< Discard frame buffer attachment 5.
exports.CLEAR_DISCARD_COLOR_6 = 0x0200; //!< Discard frame buffer attachment 6.
exports.CLEAR_DISCARD_COLOR_7 = 0x0400; //!< Discard frame buffer attachment 7.
exports.CLEAR_DISCARD_DEPTH = 0x0800; //!< Discard frame buffer depth attachment.
exports.CLEAR_DISCARD_STENCIL = 0x1000; //!< Discard frame buffer stencil attachment.

///
exports.CLEAR_DISCARD_COLOR_MASK =
  exports.CLEAR_DISCARD_COLOR_0 |
  exports.CLEAR_DISCARD_COLOR_1 |
  exports.CLEAR_DISCARD_COLOR_2 |
  exports.CLEAR_DISCARD_COLOR_3 |
  exports.CLEAR_DISCARD_COLOR_4 |
  exports.CLEAR_DISCARD_COLOR_5 |
  exports.CLEAR_DISCARD_COLOR_6 |
  exports.CLEAR_DISCARD_COLOR_7;

///
exports.CLEAR_DISCARD_MASK =
  exports.CLEAR_DISCARD_COLOR_MASK |
  exports.CLEAR_DISCARD_DEPTH |
  exports.CLEAR_DISCARD_STENCIL;

///
exports.DEBUG_NONE = 0x00000000; //!< No debug.
exports.DEBUG_WIREFRAME = 0x00000001; //!< Enable wireframe for all primitives.
exports.DEBUG_IFH = 0x00000002; //!< Enable infinitely fast hardware test. No draw calls will be submitted to driver. It’s useful when profiling to quickly assess bottleneck between CPU and GPU.
exports.DEBUG_STATS = 0x00000004; //!< Enable statistics display.
exports.DEBUG_TEXT = 0x00000008; //!< Enable debug text display.
exports.DEBUG_PROFILER = 0x00000010; //!< Enable profiler.

///
exports.BUFFER_NONE = 0x0000; //!<

///
exports.BUFFER_COMPUTE_FORMAT_8x1 = 0x0001; //!< 1 8-bit value
exports.BUFFER_COMPUTE_FORMAT_8x2 = 0x0002; //!< 2 8-bit values
exports.BUFFER_COMPUTE_FORMAT_8x4 = 0x0003; //!< 4 8-bit values
exports.BUFFER_COMPUTE_FORMAT_16x1 = 0x0004; //!< 1 16-bit value
exports.BUFFER_COMPUTE_FORMAT_16x2 = 0x0005; //!< 2 16-bit values
exports.BUFFER_COMPUTE_FORMAT_16x4 = 0x0006; //!< 4 16-bit values
exports.BUFFER_COMPUTE_FORMAT_32x1 = 0x0007; //!< 1 32-bit value
exports.BUFFER_COMPUTE_FORMAT_32x2 = 0x0008; //!< 2 32-bit values
exports.BUFFER_COMPUTE_FORMAT_32x4 = 0x0009; //!< 4 32-bit values
exports.BUFFER_COMPUTE_FORMAT_SHIFT = 0; //!<
exports.BUFFER_COMPUTE_FORMAT_MASK = 0x000f; //!<

///
exports.BUFFER_COMPUTE_TYPE_INT = 0x0010; //!< Type `int`.
exports.BUFFER_COMPUTE_TYPE_UINT = 0x0020; //!< Type `uint`.
exports.BUFFER_COMPUTE_TYPE_FLOAT = 0x0030; //!< Type `float`.
exports.BUFFER_COMPUTE_TYPE_SHIFT = 4; //!<
exports.BUFFER_COMPUTE_TYPE_MASK = 0x0030; //!<

///
exports.BUFFER_COMPUTE_READ = 0x0100; //!< Buffer will be read by shader.
exports.BUFFER_COMPUTE_WRITE = 0x0200; //!< Buffer will be used for writing.
exports.BUFFER_DRAW_INDIRECT = 0x0400; //!< Buffer will be used for storing draw indirect commands.
exports.BUFFER_ALLOW_RESIZE = 0x0800; //!< Allow dynamic index/vertex buffer resize during update.
exports.BUFFER_INDEX32 = 0x1000; //!< Index buffer contains 32-bit indices.

///
exports.BUFFER_COMPUTE_READ_WRITE =
  exports.BUFFER_COMPUTE_READ | exports.BUFFER_COMPUTE_WRITE;

/// Texture creation flags.
exports.TEXTURE_NONE = BigInt(0x0000000000000000); //!<
exports.TEXTURE_MSAA_SAMPLE = BigInt(0x0000000800000000); //!< Texture will be used for MSAA sampling.
exports.TEXTURE_RT = BigInt(0x0000001000000000); //!< Render target no MSAA.
exports.TEXTURE_RT_MSAA_X2 = BigInt(0x0000002000000000); //!< Render target MSAAx2 mode.
exports.TEXTURE_RT_MSAA_X4 = BigInt(0x0000003000000000); //!< Render target MSAAx4 mode.
exports.TEXTURE_RT_MSAA_X8 = BigInt(0x0000004000000000); //!< Render target MSAAx8 mode.
exports.TEXTURE_RT_MSAA_X16 = BigInt(0x0000005000000000); //!< Render target MSAAx16 mode.
exports.TEXTURE_RT_MSAA_SHIFT = 36; //!<
exports.TEXTURE_RT_MSAA_MASK = BigInt(0x0000007000000000); //!<
exports.TEXTURE_RT_WRITE_ONLY = BigInt(0x0000008000000000); //!< Render target will be used for writing only.
exports.TEXTURE_RT_MASK = BigInt(0x000000f000000000); //!<
exports.TEXTURE_COMPUTE_WRITE = BigInt(0x0000100000000000); //!< Texture will be used for compute write.
exports.TEXTURE_SRGB = BigInt(0x0000200000000000); //!< Sample texture as sRGB.
exports.TEXTURE_BLIT_DST = BigInt(0x0000400000000000); //!< Texture will be used as blit destination.
exports.TEXTURE_READ_BACK = BigInt(0x0000800000000000); //!< Texture will be used for read back from GPU.

/// Sampler flags.
exports.SAMPLER_NONE = 0x00000000; //!<
exports.SAMPLER_U_MIRROR = 0x00000001; //!< Wrap U mode: Mirror
exports.SAMPLER_U_CLAMP = 0x00000002; //!< Wrap U mode: Clamp
exports.SAMPLER_U_BORDER = 0x00000003; //!< Wrap U mode: Border
exports.SAMPLER_U_SHIFT = 0; //!<
exports.SAMPLER_U_MASK = 0x00000003; //!<
exports.SAMPLER_V_MIRROR = 0x00000004; //!< Wrap V mode: Mirror
exports.SAMPLER_V_CLAMP = 0x00000008; //!< Wrap V mode: Clamp
exports.SAMPLER_V_BORDER = 0x0000000c; //!< Wrap V mode: Border
exports.SAMPLER_V_SHIFT = 2; //!<
exports.SAMPLER_V_MASK = 0x0000000c; //!<
exports.SAMPLER_W_MIRROR = 0x00000010; //!< Wrap W mode: Mirror
exports.SAMPLER_W_CLAMP = 0x00000020; //!< Wrap W mode: Clamp
exports.SAMPLER_W_BORDER = 0x00000030; //!< Wrap W mode: Border
exports.SAMPLER_W_SHIFT = 4; //!<
exports.SAMPLER_W_MASK = 0x00000030; //!<
exports.SAMPLER_MIN_POINT = 0x00000040; //!< Min sampling mode: Point
exports.SAMPLER_MIN_ANISOTROPIC = 0x00000080; //!< Min sampling mode: Anisotropic
exports.SAMPLER_MIN_SHIFT = 6; //!<
exports.SAMPLER_MIN_MASK = 0x000000c0; //!<
exports.SAMPLER_MAG_POINT = 0x00000100; //!< Mag sampling mode: Point
exports.SAMPLER_MAG_ANISOTROPIC = 0x00000200; //!< Mag sampling mode: Anisotropic
exports.SAMPLER_MAG_SHIFT = 8; //!<
exports.SAMPLER_MAG_MASK = 0x00000300; //!<
exports.SAMPLER_MIP_POINT = 0x00000400; //!< Mip sampling mode: Point
exports.SAMPLER_MIP_SHIFT = 10; //!<
exports.SAMPLER_MIP_MASK = 0x00000400; //!<
exports.SAMPLER_COMPARE_LESS = 0x00010000; //!< Compare when sampling depth texture: less.
exports.SAMPLER_COMPARE_LEQUAL = 0x00020000; //!< Compare when sampling depth texture: less or equal.
exports.SAMPLER_COMPARE_EQUAL = 0x00030000; //!< Compare when sampling depth texture: equal.
exports.SAMPLER_COMPARE_GEQUAL = 0x00040000; //!< Compare when sampling depth texture: greater or equal.
exports.SAMPLER_COMPARE_GREATER = 0x00050000; //!< Compare when sampling depth texture: greater.
exports.SAMPLER_COMPARE_NOTEQUAL = 0x00060000; //!< Compare when sampling depth texture: not equal.
exports.SAMPLER_COMPARE_NEVER = 0x00070000; //!< Compare when sampling depth texture: never.
exports.SAMPLER_COMPARE_ALWAYS = 0x00080000; //!< Compare when sampling depth texture: always.
exports.SAMPLER_COMPARE_SHIFT = 16; //!<
exports.SAMPLER_COMPARE_MASK = 0x000f0000; //!<
exports.SAMPLER_SAMPLE_STENCIL = 0x00100000; //!< Sample stencil instead of depth.
exports.SAMPLER_BORDER_COLOR_SHIFT = 24; //!<
exports.SAMPLER_BORDER_COLOR_MASK = 0x0f000000; //!<
exports.SAMPLER_RESERVED_SHIFT = 28; //!<
exports.SAMPLER_RESERVED_MASK = 0xf0000000; //!<

///
exports.SAMPLER_BORDER_COLOR = _index =>
  (_index << exports.SAMPLER_BORDER_COLOR_SHIFT) &
  exports.SAMPLER_BORDER_COLOR_MASK;

///
exports.SAMPLER_POINT =
  exports.SAMPLER_MIN_POINT |
  exports.SAMPLER_MAG_POINT |
  exports.SAMPLER_MIP_POINT;

///
exports.SAMPLER_UVW_MIRROR =
  exports.SAMPLER_U_MIRROR |
  exports.SAMPLER_V_MIRROR |
  exports.SAMPLER_W_MIRROR;

///
exports.SAMPLER_UVW_CLAMP =
  exports.SAMPLER_U_CLAMP | exports.SAMPLER_V_CLAMP | exports.SAMPLER_W_CLAMP;

///
exports.SAMPLER_UVW_BORDER =
  exports.SAMPLER_U_BORDER |
  exports.SAMPLER_V_BORDER |
  exports.SAMPLER_W_BORDER;

///
exports.SAMPLER_BITS_MASK =
  exports.SAMPLER_U_MASK |
  exports.SAMPLER_V_MASK |
  exports.SAMPLER_W_MASK |
  exports.SAMPLER_MIN_MASK |
  exports.SAMPLER_MAG_MASK |
  exports.SAMPLER_MIP_MASK |
  exports.SAMPLER_COMPARE_MASK;

///
exports.RESET_NONE = 0x00000000; //!< No reset flags.
exports.RESET_FULLSCREEN = 0x00000001; //!< Not supported yet.
exports.RESET_FULLSCREEN_SHIFT = 0; //!< Fullscreen bit shift.
exports.RESET_FULLSCREEN_MASK = 0x00000001; //!< Fullscreen bit mask.
exports.RESET_MSAA_X2 = 0x00000010; //!< Enable 2x MSAA.
exports.RESET_MSAA_X4 = 0x00000020; //!< Enable 4x MSAA.
exports.RESET_MSAA_X8 = 0x00000030; //!< Enable 8x MSAA.
exports.RESET_MSAA_X16 = 0x00000040; //!< Enable 16x MSAA.
exports.RESET_MSAA_SHIFT = 4; //!< MSAA mode bit shift.
exports.RESET_MSAA_MASK = 0x00000070; //!< MSAA mode bit mask.
exports.RESET_VSYNC = 0x00000080; //!< Enable V-Sync.
exports.RESET_MAXANISOTROPY = 0x00000100; //!< Turn on/off max anisotropy.
exports.RESET_CAPTURE = 0x00000200; //!< Begin screen capture.
exports.RESET_FLUSH_AFTER_RENDER = 0x00002000; //!< Flush rendering after submitting to GPU.
exports.RESET_FLIP_AFTER_RENDER = 0x00004000; //!< This flag  specifies where flip occurs. Default behavior is that flip occurs before rendering new frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
exports.RESET_SRGB_BACKBUFFER = 0x00008000; //!< Enable sRGB backbuffer.
exports.RESET_HDR10 = 0x00010000; //!< Enable HDR10 rendering.
exports.RESET_HIDPI = 0x00020000; //!< Enable HiDPI rendering.
exports.RESET_DEPTH_CLAMP = 0x00040000; //!< Enable depth clamp.
exports.RESET_SUSPEND = 0x00080000; //!< Suspend rendering.
exports.RESET_RESERVED_SHIFT = 31; //!< Internal bits shift.
exports.RESET_RESERVED_MASK = 0x80000000; //!< Internal bits mask.

///
exports.CAPS_ALPHA_TO_COVERAGE = BigInt(0x0000000000000001); //!< Alpha to coverage is supported.
exports.CAPS_BLEND_INDEPENDENT = BigInt(0x0000000000000002); //!< Blend independent is supported.
exports.CAPS_COMPUTE = BigInt(0x0000000000000004); //!< Compute shaders are supported.
exports.CAPS_CONSERVATIVE_RASTER = BigInt(0x0000000000000008); //!< Conservative rasterization is supported.
exports.CAPS_DRAW_INDIRECT = BigInt(0x0000000000000010); //!< Draw indirect is supported.
exports.CAPS_FRAGMENT_DEPTH = BigInt(0x0000000000000020); //!< Fragment depth is accessible in fragment shader.
exports.CAPS_FRAGMENT_ORDERING = BigInt(0x0000000000000040); //!< Fragment ordering is available in fragment shader.
exports.CAPS_FRAMEBUFFER_RW = BigInt(0x0000000000000080); //!< Read/Write frame buffer attachments are supported.
exports.CAPS_GRAPHICS_DEBUGGER = BigInt(0x0000000000000100); //!< Graphics debugger is present.
exports.CAPS_HDR10 = BigInt(0x0000000000000400); //!< HDR10 rendering is supported.
exports.CAPS_HIDPI = BigInt(0x0000000000000800); //!< HiDPI rendering is supported.
exports.CAPS_INDEX32 = BigInt(0x0000000000001000); //!< 32-bit indices are supported.
exports.CAPS_INSTANCING = BigInt(0x0000000000002000); //!< Instancing is supported.
exports.CAPS_OCCLUSION_QUERY = BigInt(0x0000000000004000); //!< Occlusion query is supported.
exports.CAPS_RENDERER_MULTITHREADED = BigInt(0x0000000000008000); //!< Renderer is on separate thread.
exports.CAPS_SWAP_CHAIN = BigInt(0x0000000000010000); //!< Multiple windows are supported.
exports.CAPS_TEXTURE_2D_ARRAY = BigInt(0x0000000000020000); //!< 2D texture array is supported.
exports.CAPS_TEXTURE_3D = BigInt(0x0000000000040000); //!< 3D textures are supported.
exports.CAPS_TEXTURE_BLIT = BigInt(0x0000000000080000); //!< Texture blit is supported.
exports.CAPS_TEXTURE_COMPARE_ALL = BigInt(0x0000000000300000); //!< All texture compare modes are supported.
exports.CAPS_TEXTURE_COMPARE_LEQUAL = BigInt(0x0000000000200000); //!< Texture compare less equal mode is supported.
exports.CAPS_TEXTURE_CUBE_ARRAY = BigInt(0x0000000000400000); //!< Cubemap texture array is supported.
exports.CAPS_TEXTURE_DIRECT_ACCESS = BigInt(0x0000000000800000); //!< CPU direct access to GPU texture memory.
exports.CAPS_TEXTURE_READ_BACK = BigInt(0x0000000001000000); //!< Read-back texture is supported.
exports.CAPS_VERTEX_ATTRIB_HALF = BigInt(0x0000000002000000); //!< Vertex attribute half-float is supported.
exports.CAPS_VERTEX_ATTRIB_UINT10 = BigInt(0x0000000004000000); //!< Vertex attribute 10_10_10_2 is supported.
exports.CAPS_VERTEX_ID = BigInt(0x0000000008000000); //!< Rendering with VertexID only is supported.

///
exports.CAPS_FORMAT_TEXTURE_NONE = 0x0000; //!< Texture format is not supported.
exports.CAPS_FORMAT_TEXTURE_2D = 0x0001; //!< Texture format is supported.
exports.CAPS_FORMAT_TEXTURE_2D_SRGB = 0x0002; //!< Texture as sRGB format is supported.
exports.CAPS_FORMAT_TEXTURE_2D_EMULATED = 0x0004; //!< Texture format is emulated.
exports.CAPS_FORMAT_TEXTURE_3D = 0x0008; //!< Texture format is supported.
exports.CAPS_FORMAT_TEXTURE_3D_SRGB = 0x0010; //!< Texture as sRGB format is supported.
exports.CAPS_FORMAT_TEXTURE_3D_EMULATED = 0x0020; //!< Texture format is emulated.
exports.CAPS_FORMAT_TEXTURE_CUBE = 0x0040; //!< Texture format is supported.
exports.CAPS_FORMAT_TEXTURE_CUBE_SRGB = 0x0080; //!< Texture as sRGB format is supported.
exports.CAPS_FORMAT_TEXTURE_CUBE_EMULATED = 0x0100; //!< Texture format is emulated.
exports.CAPS_FORMAT_TEXTURE_VERTEX = 0x0200; //!< Texture format can be used from vertex shader.
exports.CAPS_FORMAT_TEXTURE_IMAGE = 0x0400; //!< Texture format can be used as image from compute shader.
exports.CAPS_FORMAT_TEXTURE_FRAMEBUFFER = 0x0800; //!< Texture format can be used as frame buffer.
exports.CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA = 0x1000; //!< Texture format can be used as MSAA frame buffer.
exports.CAPS_FORMAT_TEXTURE_MSAA = 0x2000; //!< Texture can be sampled as MSAA.
exports.CAPS_FORMAT_TEXTURE_MIP_AUTOGEN = 0x4000; //!< Texture format supports auto-generated mips.

///
exports.RESOLVE_NONE = 0x00; //!< No resolve flags.
exports.RESOLVE_AUTO_GEN_MIPS = 0x01; //!< Auto-generate mip maps on resolve.

///
exports.PCI_ID_NONE = 0x0000; //!< Autoselect adapter.
exports.PCI_ID_SOFTWARE_RASTERIZER = 0x0001; //!< Software rasterizer.
exports.PCI_ID_AMD = 0x1002; //!< AMD adapter.
exports.PCI_ID_INTEL = 0x8086; //!< Intel adapter.
exports.PCI_ID_NVIDIA = 0x10de; //!< nVidia adapter.

///
exports.CUBE_MAP_POSITIVE_X = 0x00; //!< Cubemap +x.
exports.CUBE_MAP_NEGATIVE_X = 0x01; //!< Cubemap -x.
exports.CUBE_MAP_POSITIVE_Y = 0x02; //!< Cubemap +y.
exports.CUBE_MAP_NEGATIVE_Y = 0x03; //!< Cubemap -y.
exports.CUBE_MAP_POSITIVE_Z = 0x04; //!< Cubemap +z.
exports.CUBE_MAP_NEGATIVE_Z = 0x05; //!< Cubemap -z.
