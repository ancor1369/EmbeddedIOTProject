var mongooose=require('mongoose');
var types=mongoose.Schema.types;

var devices=mongoose.model('product',{
    ProductID:{type:types.String,
    required:true,unique:true},
    
    Name:{type:types.String,
        
    PriceDollar:types.String,
       
    PriceCents:types.String,
      
    Description:types.String,
        
    URL:types.String,
       
    SKU:types.String,
       
    Model:types.String,
        
    DueDate:types.Date,
        
    LayoutName:types.String,
       
    Update:types.Boolean,
       
    Blink:{type:types.String,
        required:true,default:false}
});

module.exports={product};