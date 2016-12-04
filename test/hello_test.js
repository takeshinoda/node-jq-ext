import mocha  from 'mocha'
import sinon  from 'sinon'
import assert from 'power-assert'
import node_jq_ext from '../build/Release/node_jq_ext'

describe('hello', () => {
  it('import', () => assert(node_jq_ext.test() == 'hoge'))
})

describe('JqWrapper', () => {
  it('.constructor', () => {
    const obj = new node_jq_ext.JqWrapper();
    assert(obj.constructor.name == 'JqWrapper');
  })

  it('#parse', () => {
    const obj = new node_jq_ext.JqWrapper();
    assert(obj.parse('kero') == 'kero');
  })
})

