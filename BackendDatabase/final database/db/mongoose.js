var mongoose = require('mongoose');

mongoose.Promise=global.Promise;
//mongoose.connect('mongodb://localhost/prices');
mongoose.connect('mongodb+srv://<>:<>@cluster0-oouxh.azure.mongodb.net/test?retryWrites=true&w=majority');
module.exports={mongoose};


