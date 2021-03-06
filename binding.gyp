{
  'variables': {
    'platform': '<(OS)',
  },
  'conditions': [
    ['platform == "mac"', {'variables': {'platform': 'darwin'}}],
    ['platform == "win"', {'variables': {'platform': 'win32'}}],
  ],
  'targets': [
    {
      'target_name': 'bgfx',
      'defines': [
        'NAPI_EXPERIMENTAL',
        'NAPI_ENABLE_CPP_EXCEPTIONS',
      ],
      'cflags_cc': [ '-Wall', '-pedantic', '-std=c++17' ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'sources': [
        'src/bgfx_draw.cpp',
        'src/bgfx.cpp',
        'src/bindings.cpp',
      ],
      'include_dirs': [
        '<(module_root_dir)/deps/bgfx/include',
        '<!@(node -p "require(\'napi-bind\').include")',
      ],
      "dependencies": [],
      'conditions': [
        ['platform=="linux"', {
          'library_dirs': ['<(module_root_dir)/deps/bgfx/bin/linux/x64'],
          'libraries': [
            '-Wl,-rpath,<(module_root_dir)/deps/bgfx/bin/linux/x64',
            '<(module_root_dir)/deps/bgfx/bin/linux/x64/libbgfx-shared-libRelease.so'
          ],
        }],
        ['platform=="darwin"', {
          'library_dirs': ['<(module_root_dir)/deps/bgfx/bin/darwin/x64'],
          'libraries': [
            '-Wl,-rpath,<(module_root_dir)/deps/bgfx/bin/darwin/x64',
            '<(module_root_dir)/deps/bgfx/bin/darwin/x64/libbgfx-shared-libRelease.dylib'
          ],
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'OTHER_CFLAGS': ['-std=c++17']
          },
        }],
        ['platform=="win32"', {
          'library_dirs': ['<(module_root_dir)/deps/bgfx/bin/win32/x64'],
          'libraries': ['bgfx-shared-libRelease.lib'],
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
              'files': ['<(module_root_dir)/deps/bgfx/bin/win32/x64/bgfx-shared-libRelease.dll']
            }
          ],
        }],
      ],
    }
  ]
}