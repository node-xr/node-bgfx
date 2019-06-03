#include "bgfx_converters.hpp"
#include "bgfx_draw.hpp"
#include "bgfx.hpp"
#include "wrap.hpp"
#include <bgfx/c99/bgfx.h>
#include <string.h>

void napi_bgfx_finalize_vertex_decl(napi_env env, void *finalize_data, void *finalize_hint)
{
  bgfx_vertex_decl_t *_decl = (bgfx_vertex_decl_t *)finalize_data;
  delete _decl;
}

napi_value napi_bgfx_alloc_vertex_decl(napi_env env, napi_callback_info info)
{
  bgfx_vertex_decl_t *_ret = new bgfx_vertex_decl_t;
  napi_value _napi_ret;
  ASSERT_OK(napi_create_external(env, (void *)_ret, napi_bgfx_finalize_vertex_decl, nullptr, &_napi_ret), "EINVAL", "Unknown Error.");
  return _napi_ret;
}

uint32_t bgfx_encoder_set_transform2(bgfx_encoder_t *encoder, bgfx_mat4_array_t arr)
{
  return bgfx_encoder_set_transform(encoder, arr.head, arr.count);
}

uint32_t bgfx_set_transform2(bgfx_mat4_array_t arr)
{
  return bgfx_set_transform(arr.head, arr.count);
}

void bgfx_set_view_transform2(bgfx_view_id_t view, bgfx_mat4_t *xform, bgfx_mat4_t *proj)
{
  bgfx_set_view_transform(view, static_cast<void *>(xform), static_cast<void *>(proj));
}

bool bgfx_init_minimal(void *ndt, void *nwh, uint32_t width, uint32_t height, uint32_t reset)
{
  bgfx_init_t init;
  bgfx_init_ctor(&init);
  init.platformData.ndt = ndt;
  init.platformData.nwh = nwh;
  init.resolution.width = width;
  init.resolution.height = height;
  init.resolution.reset = reset;
  return bgfx_init(&init);
}

bool bgfx_init_headless()
{
  bgfx_init_t init;
  bgfx_init_ctor(&init);
  init.type = BGFX_RENDERER_TYPE_NOOP;
  return bgfx_init(&init);
}

void bgfx_dbg_text_print(uint16_t x, uint16_t y, uint8_t attr, const std::string text)
{
  bgfx_dbg_text_printf(x, y, attr, "%s", text.c_str());
}

napi_value create_bgfx(napi_env env)
{
  napi_value exports;
  ASSERT_OK(napi_create_object(env, &exports), "EINVAL", "Failed to create exports.");

  wrap::set_function(env, exports, "vertex_decl_begin", bgfx_vertex_decl_begin);
  wrap::set_function(env, exports, "vertex_decl_add", bgfx_vertex_decl_add);
  wrap::set_function(env, exports, "vertex_decl_has", bgfx_vertex_decl_has);
  wrap::set_function(env, exports, "vertex_decl_skip", bgfx_vertex_decl_skip);
  wrap::set_function(env, exports, "vertex_decl_end", bgfx_vertex_decl_end);
  wrap::set_function(env, exports, "vertex_convert", bgfx_vertex_convert);
  wrap::set_function(env, exports, "topology_convert", bgfx_topology_convert);
  wrap::set_function(env, exports, "get_renderer_name", bgfx_get_renderer_name);
  wrap::set_function(env, exports, "shutdown", bgfx_shutdown);
  wrap::set_function(env, exports, "reset", bgfx_reset);
  wrap::set_function(env, exports, "frame", bgfx_frame);
  wrap::set_function(env, exports, "get_renderer_type", bgfx_get_renderer_type);
  wrap::set_function(env, exports, "set_debug", bgfx_set_debug);
  wrap::set_function(env, exports, "dbg_text_clear", bgfx_dbg_text_clear);
  wrap::set_function(env, exports, "dbg_text_print", bgfx_dbg_text_print);
  wrap::set_function(env, exports, "dbg_text_image", bgfx_dbg_text_image);
  wrap::set_function(env, exports, "create_index_buffer", bgfx_create_index_buffer);
  wrap::set_function(env, exports, "destroy_index_buffer", bgfx_destroy_index_buffer);
  wrap::set_function(env, exports, "set_index_buffer_name", bgfx_set_index_buffer_name);
  wrap::set_function(env, exports, "create_vertex_buffer", bgfx_create_vertex_buffer);
  wrap::set_function(env, exports, "destroy_vertex_buffer", bgfx_destroy_vertex_buffer);
  wrap::set_function(env, exports, "set_vertex_buffer_name", bgfx_set_vertex_buffer_name);
  wrap::set_function(env, exports, "create_dynamic_index_buffer", bgfx_create_dynamic_index_buffer);
  wrap::set_function(env, exports, "create_dynamic_index_buffer_mem", bgfx_create_dynamic_index_buffer_mem);
  wrap::set_function(env, exports, "destroy_dynamic_index_buffer", bgfx_destroy_dynamic_index_buffer);
  wrap::set_function(env, exports, "update_dynamic_index_buffer", bgfx_update_dynamic_index_buffer);
  wrap::set_function(env, exports, "create_dynamic_vertex_buffer", bgfx_create_dynamic_vertex_buffer);
  wrap::set_function(env, exports, "create_dynamic_vertex_buffer_mem", bgfx_create_dynamic_vertex_buffer_mem);
  wrap::set_function(env, exports, "destroy_dynamic_vertex_buffer", bgfx_destroy_dynamic_vertex_buffer);
  wrap::set_function(env, exports, "update_dynamic_vertex_buffer", bgfx_update_dynamic_vertex_buffer);
  wrap::set_function(env, exports, "get_avail_transient_index_buffer", bgfx_get_avail_transient_index_buffer);
  wrap::set_function(env, exports, "get_avail_transient_vertex_buffer", bgfx_get_avail_transient_vertex_buffer);
  wrap::set_function(env, exports, "get_avail_instance_data_buffer", bgfx_get_avail_instance_data_buffer);
  wrap::set_function(env, exports, "create_indirect_buffer", bgfx_create_indirect_buffer);
  wrap::set_function(env, exports, "destroy_indirect_buffer", bgfx_destroy_indirect_buffer);
  wrap::set_function(env, exports, "create_shader", bgfx_create_shader);
  wrap::set_function(env, exports, "destroy_shader", bgfx_destroy_shader);
  wrap::set_function(env, exports, "set_shader_name", bgfx_set_shader_name);
  wrap::set_function(env, exports, "create_program", bgfx_create_program);
  wrap::set_function(env, exports, "destroy_program", bgfx_destroy_program);
  wrap::set_function(env, exports, "create_compute_program", bgfx_create_compute_program);
  wrap::set_function(env, exports, "is_texture_valid", bgfx_is_texture_valid);
  wrap::set_function(env, exports, "calc_texture_size", bgfx_calc_texture_size);
  wrap::set_function(env, exports, "create_texture", bgfx_create_texture);
  wrap::set_function(env, exports, "create_texture_2d", bgfx_create_texture_2d);
  wrap::set_function(env, exports, "create_texture_2d_scaled", bgfx_create_texture_2d_scaled);
  wrap::set_function(env, exports, "create_texture_3d", bgfx_create_texture_3d);
  wrap::set_function(env, exports, "create_texture_cube", bgfx_create_texture_cube);
  wrap::set_function(env, exports, "destroy_texture", bgfx_destroy_texture);
  wrap::set_function(env, exports, "update_texture_2d", bgfx_update_texture_2d);
  wrap::set_function(env, exports, "update_texture_3d", bgfx_update_texture_3d);
  wrap::set_function(env, exports, "update_texture_cube", bgfx_update_texture_cube);
  wrap::set_function(env, exports, "read_texture", bgfx_read_texture);
  wrap::set_function(env, exports, "set_texture_name", bgfx_set_texture_name);
  wrap::set_function(env, exports, "create_frame_buffer", bgfx_create_frame_buffer);
  wrap::set_function(env, exports, "create_frame_buffer_scaled", bgfx_create_frame_buffer_scaled);
  wrap::set_function(env, exports, "create_frame_buffer_from_nwh", bgfx_create_frame_buffer_from_nwh);
  wrap::set_function(env, exports, "destroy_frame_buffer", bgfx_destroy_frame_buffer);
  wrap::set_function(env, exports, "set_frame_buffer_name", bgfx_set_frame_buffer_name);
  wrap::set_function(env, exports, "get_texture", bgfx_get_texture);
  wrap::set_function(env, exports, "create_uniform", bgfx_create_uniform);
  wrap::set_function(env, exports, "destroy_uniform", bgfx_destroy_uniform);
  wrap::set_function(env, exports, "create_occlusion_query", bgfx_create_occlusion_query);
  wrap::set_function(env, exports, "destroy_occlusion_query", bgfx_destroy_occlusion_query);
  wrap::set_function(env, exports, "set_palette_color_rgba8", bgfx_set_palette_color_rgba8);
  wrap::set_function(env, exports, "set_view_name", bgfx_set_view_name);
  wrap::set_function(env, exports, "set_view_rect", bgfx_set_view_rect);
  wrap::set_function(env, exports, "set_view_rect_ratio", bgfx_set_view_rect_ratio);
  wrap::set_function(env, exports, "set_view_scissor", bgfx_set_view_scissor);
  wrap::set_function(env, exports, "set_view_clear", bgfx_set_view_clear);
  wrap::set_function(env, exports, "set_view_clear_mrt", bgfx_set_view_clear_mrt);
  wrap::set_function(env, exports, "set_view_mode", bgfx_set_view_mode);
  wrap::set_function(env, exports, "set_view_frame_buffer", bgfx_set_view_frame_buffer);
  wrap::set_function(env, exports, "set_view_transform", bgfx_set_view_transform2);
  wrap::set_function(env, exports, "encoder_begin", bgfx_encoder_begin);
  wrap::set_function(env, exports, "encoder_end", bgfx_encoder_end);
  wrap::set_function(env, exports, "encoder_set_marker", bgfx_encoder_set_marker);
  wrap::set_function(env, exports, "encoder_set_state", bgfx_encoder_set_state);
  wrap::set_function(env, exports, "encoder_set_condition", bgfx_encoder_set_condition);
  wrap::set_function(env, exports, "encoder_set_stencil", bgfx_encoder_set_stencil);
  wrap::set_function(env, exports, "encoder_set_scissor", bgfx_encoder_set_scissor);
  wrap::set_function(env, exports, "encoder_set_scissor_cached", bgfx_encoder_set_scissor_cached);
  wrap::set_function(env, exports, "encoder_set_transform", bgfx_encoder_set_transform2);
  wrap::set_function(env, exports, "encoder_set_transform_cached", bgfx_encoder_set_transform_cached);
  wrap::set_function(env, exports, "encoder_set_uniform", bgfx_encoder_set_uniform);
  wrap::set_function(env, exports, "encoder_set_index_buffer", bgfx_encoder_set_index_buffer);
  wrap::set_function(env, exports, "encoder_set_dynamic_index_buffer", bgfx_encoder_set_dynamic_index_buffer);
  wrap::set_function(env, exports, "encoder_set_vertex_buffer", bgfx_encoder_set_vertex_buffer);
  wrap::set_function(env, exports, "encoder_set_dynamic_vertex_buffer", bgfx_encoder_set_dynamic_vertex_buffer);
  wrap::set_function(env, exports, "encoder_set_vertex_count", bgfx_encoder_set_vertex_count);
  wrap::set_function(env, exports, "encoder_set_instance_data_from_vertex_buffer", bgfx_encoder_set_instance_data_from_vertex_buffer);
  wrap::set_function(env, exports, "encoder_set_instance_data_from_dynamic_vertex_buffer", bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer);
  wrap::set_function(env, exports, "encoder_set_instance_count", bgfx_encoder_set_instance_count);
  wrap::set_function(env, exports, "encoder_set_texture", bgfx_encoder_set_texture);
  wrap::set_function(env, exports, "encoder_touch", bgfx_encoder_touch);
  wrap::set_function(env, exports, "encoder_submit", bgfx_encoder_submit);
  wrap::set_function(env, exports, "encoder_submit_occlusion_query", bgfx_encoder_submit_occlusion_query);
  wrap::set_function(env, exports, "encoder_submit_indirect", bgfx_encoder_submit_indirect);
  wrap::set_function(env, exports, "encoder_set_compute_index_buffer", bgfx_encoder_set_compute_index_buffer);
  wrap::set_function(env, exports, "encoder_set_compute_vertex_buffer", bgfx_encoder_set_compute_vertex_buffer);
  wrap::set_function(env, exports, "encoder_set_compute_dynamic_index_buffer", bgfx_encoder_set_compute_dynamic_index_buffer);
  wrap::set_function(env, exports, "encoder_set_compute_dynamic_vertex_buffer", bgfx_encoder_set_compute_dynamic_vertex_buffer);
  wrap::set_function(env, exports, "encoder_set_compute_indirect_buffer", bgfx_encoder_set_compute_indirect_buffer);
  wrap::set_function(env, exports, "encoder_set_image", bgfx_encoder_set_image);
  wrap::set_function(env, exports, "encoder_dispatch", bgfx_encoder_dispatch);
  wrap::set_function(env, exports, "encoder_dispatch_indirect", bgfx_encoder_dispatch_indirect);
  wrap::set_function(env, exports, "encoder_discard", bgfx_encoder_discard);
  wrap::set_function(env, exports, "encoder_blit", bgfx_encoder_blit);
  wrap::set_function(env, exports, "request_screen_shot", bgfx_request_screen_shot);
  wrap::set_function(env, exports, "render_frame", bgfx_render_frame);
  wrap::set_function(env, exports, "set_platform_data", bgfx_set_platform_data);
  wrap::set_function(env, exports, "set_marker", bgfx_set_marker);
  wrap::set_function(env, exports, "set_state", bgfx_set_state);
  wrap::set_function(env, exports, "set_condition", bgfx_set_condition);
  wrap::set_function(env, exports, "set_stencil", bgfx_set_stencil);
  wrap::set_function(env, exports, "set_scissor", bgfx_set_scissor);
  wrap::set_function(env, exports, "set_scissor_cached", bgfx_set_scissor_cached);
  wrap::set_function(env, exports, "set_transform", bgfx_set_transform2);
  wrap::set_function(env, exports, "set_transform_cached", bgfx_set_transform_cached);
  wrap::set_function(env, exports, "set_uniform", bgfx_set_uniform);
  wrap::set_function(env, exports, "set_index_buffer", bgfx_set_index_buffer);
  wrap::set_function(env, exports, "set_dynamic_index_buffer", bgfx_set_dynamic_index_buffer);
  wrap::set_function(env, exports, "set_vertex_buffer", bgfx_set_vertex_buffer);
  wrap::set_function(env, exports, "set_dynamic_vertex_buffer", bgfx_set_dynamic_vertex_buffer);
  wrap::set_function(env, exports, "set_vertex_count", bgfx_set_vertex_count);
  wrap::set_function(env, exports, "set_instance_data_from_vertex_buffer", bgfx_set_instance_data_from_vertex_buffer);
  wrap::set_function(env, exports, "set_instance_data_from_dynamic_vertex_buffer", bgfx_set_instance_data_from_dynamic_vertex_buffer);
  wrap::set_function(env, exports, "set_instance_count", bgfx_set_instance_count);
  wrap::set_function(env, exports, "set_texture", bgfx_set_texture);
  wrap::set_function(env, exports, "touch", bgfx_touch);
  wrap::set_function(env, exports, "submit", bgfx_submit);
  wrap::set_function(env, exports, "submit_occlusion_query", bgfx_submit_occlusion_query);
  wrap::set_function(env, exports, "submit_indirect", bgfx_submit_indirect);
  wrap::set_function(env, exports, "set_compute_index_buffer", bgfx_set_compute_index_buffer);
  wrap::set_function(env, exports, "set_compute_vertex_buffer", bgfx_set_compute_vertex_buffer);
  wrap::set_function(env, exports, "set_compute_dynamic_index_buffer", bgfx_set_compute_dynamic_index_buffer);
  wrap::set_function(env, exports, "set_compute_dynamic_vertex_buffer", bgfx_set_compute_dynamic_vertex_buffer);
  wrap::set_function(env, exports, "set_compute_indirect_buffer", bgfx_set_compute_indirect_buffer);
  wrap::set_function(env, exports, "set_image", bgfx_set_image);
  wrap::set_function(env, exports, "dispatch", bgfx_dispatch);
  wrap::set_function(env, exports, "dispatch_indirect", bgfx_dispatch_indirect);
  wrap::set_function(env, exports, "discard", bgfx_discard);
  wrap::set_function(env, exports, "blit", bgfx_blit);
  wrap::set_function(env, exports, "init_minimal", bgfx_init_minimal);
  wrap::set_function(env, exports, "init_headless", bgfx_init_headless);
  wrap::set_function(env, exports, "draw", bgfx_draw);
  export_function(env, exports, "alloc_vertex_decl", napi_bgfx_alloc_vertex_decl);
  return exports;
}
