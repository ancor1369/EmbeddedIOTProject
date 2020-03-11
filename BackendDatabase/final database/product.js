const express = require('express')
const app = express()
const port = 7000
const testData = {
  name: 'John Doe',
  age: '30',
  account_balance: '15.5'
}
app.get('/', (req, res) => res.send(testData))
app.listen(port, () => console.log(`Server listening on port ${port}`))