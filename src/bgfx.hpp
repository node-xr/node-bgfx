// Autogenerated -- DO NOT EDIT 
#pragma once
#include "util.hpp"
#include <node_api.h>

napi_value create_bgfx(napi_env env);

//napi_value nbgfx_vertex_pack(napi_env env, napi_callback_info info);
//napi_value nbgfx_vertex_unpack(napi_env env, napi_callback_info info);
napi_value nbgfx_vertex_convert(napi_env env, napi_callback_info info);
//napi_value nbgfx_weld_vertices(napi_env env, napi_callback_info info);
napi_value nbgfx_topology_convert(napi_env env, napi_callback_info info);
//napi_value nbgfx_topology_sort_tri_list(napi_env env, napi_callback_info info);
//napi_value nbgfx_get_supported_renderers(napi_env env, napi_callback_info info);
napi_value nbgfx_get_renderer_name(napi_env env, napi_callback_info info);
//napi_value nbgfx_init_ctor(napi_env env, napi_callback_info info);
//napi_value nbgfx_init(napi_env env, napi_callback_info info);
napi_value nbgfx_shutdown(napi_env env, napi_callback_info info);
napi_value nbgfx_reset(napi_env env, napi_callback_info info);
napi_value nbgfx_frame(napi_env env, napi_callback_info info);
napi_value nbgfx_get_renderer_type(napi_env env, napi_callback_info info);
//napi_value nbgfx_get_caps(napi_env env, napi_callback_info info);
//napi_value nbgfx_get_stats(napi_env env, napi_callback_info info);
//napi_value nbgfx_alloc(napi_env env, napi_callback_info info);
//napi_value nbgfx_copy(napi_env env, napi_callback_info info);
//napi_value nbgfx_make_ref(napi_env env, napi_callback_info info);
//napi_value nbgfx_make_ref_release(napi_env env, napi_callback_info info);
napi_value nbgfx_set_debug(napi_env env, napi_callback_info info);
napi_value nbgfx_dbg_text_clear(napi_env env, napi_callback_info info);
napi_value nbgfx_dbg_text_printf(napi_env env, napi_callback_info info);
//napi_value nbgfx_dbg_text_vprintf(napi_env env, napi_callback_info info);
napi_value nbgfx_dbg_text_image(napi_env env, napi_callback_info info);
napi_value nbgfx_create_index_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_set_index_buffer_name(napi_env env, napi_callback_info info);
napi_value nbgfx_destroy_index_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_create_vertex_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_set_vertex_buffer_name(napi_env env, napi_callback_info info);
napi_value nbgfx_destroy_vertex_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_create_dynamic_index_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_create_dynamic_index_buffer_mem(napi_env env, napi_callback_info info);
napi_value nbgfx_update_dynamic_index_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_destroy_dynamic_index_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_create_dynamic_vertex_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_create_dynamic_vertex_buffer_mem(napi_env env, napi_callback_info info);
napi_value nbgfx_update_dynamic_vertex_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_destroy_dynamic_vertex_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_get_avail_transient_index_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_get_avail_transient_vertex_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_get_avail_instance_data_buffer(napi_env env, napi_callback_info info);
//napi_value nbgfx_alloc_transient_index_buffer(napi_env env, napi_callback_info info);
//napi_value nbgfx_alloc_transient_vertex_buffer(napi_env env, napi_callback_info info);
//napi_value nbgfx_alloc_transient_buffers(napi_env env, napi_callback_info info);
//napi_value nbgfx_alloc_instance_data_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_create_indirect_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_destroy_indirect_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_create_shader(napi_env env, napi_callback_info info);
//napi_value nbgfx_get_shader_uniforms(napi_env env, napi_callback_info info);
napi_value nbgfx_set_shader_name(napi_env env, napi_callback_info info);
napi_value nbgfx_destroy_shader(napi_env env, napi_callback_info info);
napi_value nbgfx_create_program(napi_env env, napi_callback_info info);
napi_value nbgfx_create_compute_program(napi_env env, napi_callback_info info);
napi_value nbgfx_destroy_program(napi_env env, napi_callback_info info);
napi_value nbgfx_is_texture_valid(napi_env env, napi_callback_info info);
//napi_value nbgfx_calc_texture_size(napi_env env, napi_callback_info info);
//napi_value nbgfx_create_texture(napi_env env, napi_callback_info info);
napi_value nbgfx_create_texture_2d(napi_env env, napi_callback_info info);
napi_value nbgfx_create_texture_2d_scaled(napi_env env, napi_callback_info info);
napi_value nbgfx_create_texture_3d(napi_env env, napi_callback_info info);
napi_value nbgfx_create_texture_cube(napi_env env, napi_callback_info info);
napi_value nbgfx_update_texture_2d(napi_env env, napi_callback_info info);
napi_value nbgfx_update_texture_3d(napi_env env, napi_callback_info info);
napi_value nbgfx_update_texture_cube(napi_env env, napi_callback_info info);
napi_value nbgfx_read_texture(napi_env env, napi_callback_info info);
napi_value nbgfx_set_texture_name(napi_env env, napi_callback_info info);
//napi_value nbgfx_get_direct_access_ptr(napi_env env, napi_callback_info info);
napi_value nbgfx_destroy_texture(napi_env env, napi_callback_info info);
napi_value nbgfx_create_frame_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_create_frame_buffer_scaled(napi_env env, napi_callback_info info);
//napi_value nbgfx_create_frame_buffer_from_handles(napi_env env, napi_callback_info info);
//napi_value nbgfx_create_frame_buffer_from_attachment(napi_env env, napi_callback_info info);
napi_value nbgfx_create_frame_buffer_from_nwh(napi_env env, napi_callback_info info);
napi_value nbgfx_set_frame_buffer_name(napi_env env, napi_callback_info info);
napi_value nbgfx_get_texture(napi_env env, napi_callback_info info);
napi_value nbgfx_destroy_frame_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_create_uniform(napi_env env, napi_callback_info info);
//napi_value nbgfx_get_uniform_info(napi_env env, napi_callback_info info);
napi_value nbgfx_destroy_uniform(napi_env env, napi_callback_info info);
napi_value nbgfx_create_occlusion_query(napi_env env, napi_callback_info info);
//napi_value nbgfx_get_result(napi_env env, napi_callback_info info);
napi_value nbgfx_destroy_occlusion_query(napi_env env, napi_callback_info info);
//napi_value nbgfx_set_palette_color(napi_env env, napi_callback_info info);
napi_value nbgfx_set_palette_color_rgba8(napi_env env, napi_callback_info info);
napi_value nbgfx_set_view_name(napi_env env, napi_callback_info info);
napi_value nbgfx_set_view_rect(napi_env env, napi_callback_info info);
napi_value nbgfx_set_view_rect_ratio(napi_env env, napi_callback_info info);
napi_value nbgfx_set_view_scissor(napi_env env, napi_callback_info info);
napi_value nbgfx_set_view_clear(napi_env env, napi_callback_info info);
napi_value nbgfx_set_view_clear_mrt(napi_env env, napi_callback_info info);
napi_value nbgfx_set_view_mode(napi_env env, napi_callback_info info);
napi_value nbgfx_set_view_frame_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_set_view_transform(napi_env env, napi_callback_info info);
//napi_value nbgfx_set_view_order(napi_env env, napi_callback_info info);
//napi_value nbgfx_encoder_begin(napi_env env, napi_callback_info info);
//napi_value nbgfx_encoder_end(napi_env env, napi_callback_info info);
napi_value nbgfx_request_screen_shot(napi_env env, napi_callback_info info);
napi_value nbgfx_render_frame(napi_env env, napi_callback_info info);
napi_value nbgfx_set_platform_data(napi_env env, napi_callback_info info);
//napi_value nbgfx_get_internal_data(napi_env env, napi_callback_info info);
//napi_value nbgfx_override_internal_texture_ptr(napi_env env, napi_callback_info info);
//napi_value nbgfx_override_internal_texture(napi_env env, napi_callback_info info);
napi_value nbgfx_set_marker(napi_env env, napi_callback_info info);
napi_value nbgfx_set_state(napi_env env, napi_callback_info info);
napi_value nbgfx_set_condition(napi_env env, napi_callback_info info);
napi_value nbgfx_set_stencil(napi_env env, napi_callback_info info);
napi_value nbgfx_set_scissor(napi_env env, napi_callback_info info);
napi_value nbgfx_set_scissor_cached(napi_env env, napi_callback_info info);
napi_value nbgfx_set_transform(napi_env env, napi_callback_info info);
napi_value nbgfx_set_transform_cached(napi_env env, napi_callback_info info);
//napi_value nbgfx_alloc_transform(napi_env env, napi_callback_info info);
napi_value nbgfx_set_uniform(napi_env env, napi_callback_info info);
napi_value nbgfx_set_index_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_set_dynamic_index_buffer(napi_env env, napi_callback_info info);
//napi_value nbgfx_set_transient_index_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_set_vertex_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_set_dynamic_vertex_buffer(napi_env env, napi_callback_info info);
//napi_value nbgfx_set_transient_vertex_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_set_vertex_count(napi_env env, napi_callback_info info);
//napi_value nbgfx_set_instance_data_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_set_instance_data_from_vertex_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_set_instance_data_from_dynamic_vertex_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_set_instance_count(napi_env env, napi_callback_info info);
napi_value nbgfx_set_texture(napi_env env, napi_callback_info info);
napi_value nbgfx_touch(napi_env env, napi_callback_info info);
napi_value nbgfx_submit(napi_env env, napi_callback_info info);
napi_value nbgfx_submit_occlusion_query(napi_env env, napi_callback_info info);
napi_value nbgfx_submit_indirect(napi_env env, napi_callback_info info);
napi_value nbgfx_set_compute_index_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_set_compute_vertex_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_set_compute_dynamic_index_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_set_compute_dynamic_vertex_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_set_compute_indirect_buffer(napi_env env, napi_callback_info info);
napi_value nbgfx_set_image(napi_env env, napi_callback_info info);
napi_value nbgfx_dispatch(napi_env env, napi_callback_info info);
napi_value nbgfx_dispatch_indirect(napi_env env, napi_callback_info info);
napi_value nbgfx_discard(napi_env env, napi_callback_info info);
napi_value nbgfx_blit(napi_env env, napi_callback_info info);
