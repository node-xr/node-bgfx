$input v_wpos, v_color

#include "common.sh"

#if !defined(TEST_DEFINITION)
#	error "Test definition should have been defined"
#endif

void main()
{
  gl_FragColor = v_color;
}
