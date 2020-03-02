const validator=require('validator')

const getnotes=require('./notes.js')
const msg=getnotes()
console.log(msg)
console.log(validator.isEmail('2050gurwinder@gmail.com'))
