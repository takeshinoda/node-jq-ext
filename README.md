

# require

`jq`

# build

## jq installed from MacPorts

```
export CPLUS_INCLUDE_PATH=/opt/local/include
export LD_LIBRARY_PATH=/opt/local/include
```

# Amazon Linux

yum:
```
$ sudo yum groupinstall 'Development Libraries'
$ sudo yum groupinstall 'Development tools'
$ sudo yum install jq jq-devel jq-libs
```

