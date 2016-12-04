{
  "targets": [
    {
      'target_name': 'node_jq_ext',
      'sources': ['ext/jq_wrapper.cpp', 'ext/node_jq_ext.cpp'],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          }
        }]
      ]
    }
  ]
}

