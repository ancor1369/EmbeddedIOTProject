var mongoose=require('mongoose');
var types=mongoose.Schema.Types;

var label=mongoose.model('label',{
    labelID:{type:types.String,
    required:true,unique:true},
    
    labelnumber:types.String,
        
    labelname:types.String,
       
       
    Blink:{type:types.String,
        required:true,default:false}
});

module.exports={label};