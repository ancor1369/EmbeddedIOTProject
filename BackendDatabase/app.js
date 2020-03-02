const validator=require('validator')

const getnotes=require('./notes.js')
const msg=getnotes()
console.log(msg)
console.log(validator.isEmail('2050gurwinder@gmail.com'))
console.log(validator.isURL('https://www.google.com'))