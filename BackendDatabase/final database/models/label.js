var mongoose=require('mongoose');
var types=mongoose.Schema.Types;

var label=mongoose.model('label',{
    LabelNumber:{type:types.String,
    required:true,unique:true},

    LabelName:types.String,
       
});

module.exports={label};