var mongooose=require('mongoose');
var types=mongoose.Schema.types;

var devices=mongoose.model('product',{
    ProductID:{type:types.string,
    required:true,unique:true},
    
    Name:{type:types.string,
        
    PriceDollar:types.string,
       
    PriceCents:types.string,
      
    Description:types.string,
        
    URL:types.string,
       
    SKU:types.string,
       
    Model:types.string,
        
    DueDate:types.date,
        
    LayoutName:types.string,
       
    Update:types.boolean,
       
    Blink:{type:types.string,
        required:true,default:false}
});

module.exports={product};