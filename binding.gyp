{
  "targets": [
    {
      'target_name': 'node-jq-ext',
      'sources': ['ext/jq_wrapper.cpp', 'ext/jq.cpp', 'ext/node_jq_ext.cpp'],
      'include_dirs': ['<!(node -e "require(\'nan\')")'],
      'cflags': ['-std=c++11'],
      'cflags!': ['-fno-exceptions'],
      'cflags_cc!': ['-fno-exceptions'],
      'libraries': ['-ljq'],
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'MACOSX_DEPLOYMENT_TARGET': '10.9',
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'OTHER_CFLAGS': ['-stdlib=libc++']
          },
        }]
      ]
    }
  ]
}

