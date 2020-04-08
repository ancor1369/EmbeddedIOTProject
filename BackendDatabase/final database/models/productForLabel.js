var mongoose=require('mongoose');
var types=mongoose.Schema.Types;

var productForLabel=mongoose.model('productForLabel',{
    DeviceID:{type:types.String,
    required:true,unique:true},

    DeviceID:types.String,
       
});

module.exports={productForLabel};