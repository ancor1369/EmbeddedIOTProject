const express = require('express')
const app = express()
const port = 7000
const productData = {
    ProductID:'46',
    Name:"mouse",
    PriceDollar:'20',
    PriceCents:'97',
    Description:"wireless optical mouse",
    URL:"https://bit.ly/largo1",
    SKU:'4532324',
    Model:"FM7544", 
    DueDate:'2018-11-22T05:00:00.000+00:00',
    LayoutName:"RegularTag",
    Update:"true",
    Blink:"False"
}
app.get('/', (req, res) => res.send(productData))
app.listen(port, () => console.log(`Server listening on port ${port}`))