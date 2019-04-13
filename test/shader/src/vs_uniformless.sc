$input a_position, a_color0
$output v_wpos, v_color

#include "common.sh"

#if !defined(TEST_DEFINITION)
#	error "Test definition should have been defined"
#endif

void main()
{
  vec3 wpos = mul(u_model[0], vec4(a_position, 1.0) ).xyz;
  gl_Position = mul(u_viewProj, vec4(wpos, 1.0) );

  v_wpos = wpos;
  v_color = a_color0;
}