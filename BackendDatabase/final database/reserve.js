
class Database {
    constructor() {
      this._connect()
    }
    
  _connect() {
       mongoose.connect(`mongodb://${server}/${database}`)
         .then(() => {
           console.log('Database connection successful')
         })
         .catch(err => {
           console.error('Database connection error')
         })
    }
  }
  const schema = {
      name: { type: mongoose.SchemaTypes.String, required: true },
      email: { type: mongoose.SchemaTypes.String, required: true },
      password: { 
          type: mongoose.SchemaTypes.String, 
          required: true, 
          select: false,
          
      }
  };
  const collectionName = "product";
  const productSchema = mongoose.Schema(schema);
  const product = mongoose.model(collectionName, productSchema);
  module.exports = product;
  
  product.create({
    name: 
    sku: 
    productid: 
  });

  const server = 'http://localhost:7000'; 
const database = 'server';      


product.findOne({
  sku:
});

product.findOne({
  sku:
}).select("+productid");