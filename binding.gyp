{
  'variables': {
    'platform': '<(OS)',
  },
  'conditions': [
    # Replace gyp platform with node platform, blech
    ['platform == "mac"', {'variables': {'platform': 'darwin'}}],
    ['platform == "win"', {'variables': {'platform': 'win32'}}],
  ],
  'targets': [
    {
      'target_name': 'bgfx',
      'defines': [
        'VERSION=98',
      ],
      'sources': [
        'src/bindings.cpp',
        'src/bgfx.cpp'
      ],
      'include_dirs': [
        "<!(node -e \"require('nan')\")",
        '<(module_root_dir)/deps/bgfx/include',
      ],
      'conditions': [
        ['OS=="linux"', {
          'library_dirs': ['<(module_root_dir)/deps/bgfx/bin/linux64'],
          'libraries': ['<(module_root_dir)/deps/bgfx/bin/linux64/libbgfx-shared-libRelease.so'],
          'copies':
          [
            {
              'destination': '<(module_root_dir)/build/Release',
              'files': ['<(module_root_dir)/deps/bgfx/bin/linux64/libbgfx-shared-libRelease.so']
            }
          ],
        }],
        ['OS=="mac"', {
          'library_dirs': ['<(module_root_dir)/deps/bgfx/bin/osx64'],
          'libraries': ['libbgfx-shared-libRelease.dylib'],
          'copies':
          [
            {
              'destination': '<(module_root_dir)/build/Release',
              'files': ['<(module_root_dir)/deps/bgfx/bin/osx64/libbgfx-shared-libRelease.dylib']
            }
          ],
        }],
        ['OS=="win"', {
          'library_dirs': ['<(module_root_dir)/deps/bgfx/bin/win64'],
          'libraries': ['libbgfx-shared-libRelease.lib'],
          'defines' : ['WIN32_LEAN_AND_MEAN', 'VC_EXTRALEAN', 'NOMINMAX'],
          'msvs_settings' : {
            'VCCLCompilerTool' : {
              'AdditionalOptions' : ['/O2','/Oy','/GL','/GF','/Gm-','/EHsc','/MT','/GS','/Gy','/GR-','/Gd']
            },
            'VCLinkerTool' : {
              'AdditionalOptions' : ['/OPT:REF','/OPT:ICF','/LTCG']
            },
          },
          'copies':
          [
            {
              'destination': '<(module_root_dir)/build/Release',
              'files': ['<(module_root_dir)/deps/bgfx/bin/win64/libbgfx-shared-libRelease.dll']
            }
          ],
        }],
      ],
    }
  ]
}