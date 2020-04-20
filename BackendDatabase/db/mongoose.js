var mongoose = require('mongoose');

mongoose.Promise=global.Promise;
mongoose.connect('mongodb://localhost/prices');
module.exports={mongoose};


