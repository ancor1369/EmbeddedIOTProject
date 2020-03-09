const express = require('express'); 
const app = express(); 
app.use(require("cors")()) 
app.use(require('body-parser').json()) 

app.get("/", (req, res) => {
  res.send("get products") 
});

app.post("/", (req, res) => {
  res.send("upload product") 
});


app.put("/", (req, res) => {
  res.send("replace a product")
});

app.patch("/", (req, res) => {
    res.send("updating a existing product")
  }); 

  app.delete("/", (req, res) => {
    res.send("delete a existing product")
  });

const port =7000;
var listener = app.listen(port, () => {
  console.log('Your app is listening on port ' + listener.address().port);
});



