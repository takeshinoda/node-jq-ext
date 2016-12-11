import mocha  from 'mocha'
import sinon  from 'sinon'
import assert from 'power-assert'
import node_jq_ext from '../index'

describe('hello', () => {
  it('import', () => assert(node_jq_ext.test() == 'hoge'))
})

describe('JqWrapper', () => {
  it('.constructor', () => {
    const obj = new node_jq_ext.Jq()
    assert(obj.constructor.name == 'Jq')
  })

  describe('#parse', () => {
    it('source: "."', () => {
      const obj = new node_jq_ext.Jq()
      assert.deepEqual(obj.parse('{"aa": 1}'), ['{"aa":1}'])
    })

    it('source: ".aa"', () => {
      const obj = new node_jq_ext.Jq('.aa')
      assert.deepEqual(obj.parse('{"aa": 1}'), ['1'])
    })

    it('source: ".aa"', () => {
      const obj = new node_jq_ext.Jq('.aa')
      assert.deepEqual(obj.parse('{"aa": "1"}'), ['"1"'])
    })

    it('source: ". | map(.aa)"', () => {
      const obj = new node_jq_ext.Jq('. | map(.aa)')
      assert.deepEqual(obj.parse('[{"aa":1},{"aa":2}]'), ['[1,2]'])
    })

    it('source: ".[] | .aa"', () => {
      const obj = new node_jq_ext.Jq('.[] | .aa')
      assert.deepEqual(obj.parse('[{"aa":1},{"aa":2}]'), ['1','2'])
    })

    describe('error pattern.', () => {
      it('source: "hoge": compile error.', () => {
        const obj = new node_jq_ext.Jq('hoge')
        assert.throws(() => { obj.parse('hoge') })
      })

      it('source: ".": input error.', () => {
        const obj = new node_jq_ext.Jq('.')
        assert.throws(()  => { obj.parse('hoge') },
                      (e) => { assert(e.message == 'Invalid numeric literal at EOF at line 1, column 4')
                               return true
                             }
                     )
      })

      it('source: undfined: => error.', () => {
        const obj = new node_jq_ext.Jq()
        assert.throws(()  => { obj.parse('hoge') })
      })

      it('source: undfined && input: undefined => error.', () => {
        const obj = new node_jq_ext.Jq()
        assert.throws(()  => { obj.parse() })
      })
    })
  })
})

