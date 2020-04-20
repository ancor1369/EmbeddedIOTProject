var mongoose=require('mongoose');
var types=mongoose.Schema.Types;

var product=mongoose.model('product',{
    ProductID:{type:types.String,
    required:true,unique:true},
    
    Name:types.String,
        
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