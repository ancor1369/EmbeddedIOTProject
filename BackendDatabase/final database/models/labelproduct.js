var mongoose=require('mongoose');
var types=mongoose.Schema.Types;

var labelproduct=mongoose.model('labelproduct',{
    LabelNumber:{type:types.String,
    required:true,unique:true},

    ProductSKU:types.String,
       
});

module.exports={labelproduct};