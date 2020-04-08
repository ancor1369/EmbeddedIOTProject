var mongoose=require('mongoose');
var types=mongoose.Schema.Types;

var productForLabel=mongoose.model('productForLabel',{
    LabelNumber:{type:types.String,
    required:true,unique:true},

    ProductSKU:types.String,
       
});

module.exports={labelproduct};