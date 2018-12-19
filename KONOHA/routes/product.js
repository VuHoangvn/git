const express = require('express');
const router = express.Router();
const multer  = require('multer');
const storage = multer.diskStorage({
  destination: function (req, file, cb) {
    cb(null, 'public/uploads')
  },
  filename: function (req, file, cb) {
    cb(null, new Date().toISOString().replace(/:/g,'-') + file.originalname);
  }
});

const upload = multer({ storage: storage });

const Cate = require('../models/category.js');
const Book = require('../models/product.js');

/* GET home page. */
router.get('/', checkAdmin, function (req, res) {
  res.redirect('admin/product/booklist')
});

router.get('/booklist', checkAdmin, function (req, res) {

  Book.find().then(function(pro){
    res.render('admin/products', {product: pro});
  });
});

router.get('/add-product', checkAdmin, function (req, res) {
  Cate.find().then(function(cate){
    res.render('admin/product_new',{errors: null, cate: cate});
  });
});

router.get('/update', checkAdmin, function (req, res) {
  Book.find().then(function(product){
    res.render('admin/products',{errors: null, product: product});
  });
});

const cpUpload = upload.fields([{ name: 'frmProductImage', maxCount: 1 }]);
router.post('/update', cpUpload, function (req, res){
   const str = req.files.frmProductImage[0].path
  const file = str.slice(-(str.length - 7));
   Book.findOne({ _id: req.body.frmProductId},  function(err, data){
      if(data === null){
        res.redirect('/')
      } else {
        data.title= req.body.frmProductTitle || data.title,
      data.imagePath= file || data.imagePath,
      data.description= req.body.frmProductDescription|| data.description,
      data.price= req.body.frmProductPrice || data.price,
      data.category=req.body.frmProductCategory || data.category,
      data.quantity= req.body.frmProductQuantity || data.quantity,
      data.author= req.body.frmProductAuthor || data.author,
      data.publisher=req.body.frmProductPublisher || data.publisher,
      data.status= req.body.frmProductPublished || data.status

      data.save();
        req.flash('success_msg', 'Modify Successful');
        res.redirect('/admin/product/booklist');
      }
                });
 });   

router.post('/add-product', checkAdmin, cpUpload, function (req, res) {
  req.checkBody('frmProductTitle', 'Name is empty').notEmpty();
  req.checkBody('frmProductAuthor', 'Author is empty').notEmpty();
  req.checkBody('frmProductPublisher', 'Publisher is empty').notEmpty();
  req.checkBody('frmProductPrice', 'Price must be a number').isInt();
  req.checkBody('frmProductDescription', 'Description is empty').notEmpty();
  const errors = req.validationErrors();
  const str = req.files.frmProductImage[0].path
  const file = str.slice(-(str.length - 7));
  console.log(file)
  // if (errors) {
  //   const file = './public/uploads/' + req.body.frmProductImage;
  //     const fs = require('fs');
  //     fs.unlink(file, function(e){
  //       if(e) throw e;
  //     });
  //     Cate.find().then(function(cate){
  //     res.render('admin/product_new',{errors: errors, cate: cate});
  //   });
  // }else{
    const book = new Book({
      title: req.body.frmProductTitle,
      imagePath: file,
      description: req.body.frmProductDescription,
      price: req.body.frmProductPrice,
      category:req.body.frmProductCategory,
      quantity: req.body.frmProductQuantity,
      author: req.body.frmProductAuthor,
      publisher:req.body.frmProductPublisher,
      status: req.body.frmProductPublished
    });

    book.save(function(err, result){
      if(err){
        return done(err);
      }
      req.flash('success_msg', 'Add Successful');
      res.redirect('/admin/product/add-product');
    });
  // }
});

router.get('/edit/:id', (req, res) => {
    Book.findById(req.params.id).then(function(product){
    Cate.find().then(function(cate){
      res.render('admin/product_edit',{errors: null, cate: cate, product: product});
    });
  });
});


router.post('/admin/product/edit/:id',  cpUpload, function (req, res) {
  req.checkBody('name', 'Name is empty').notEmpty();
  req.checkBody('author', 'Author is empty').notEmpty();
  req.checkBody('company', 'Publisher is empty').notEmpty();
  req.checkBody('price', 'Price must be a number').isInt();
  req.checkBody('des', 'Description is empty').notEmpty();

    Book.findOne({ _id: req.params.id},  function(err, data){
      data.title= req.body.frmProductTitle,
      data.imagePath= file,
      data.description= req.body.frmProductDescription,
      data.price= req.body.frmProductPrice,
      data.category=req.body.frmProductCategory,
      data.quantity= req.body.frmProductQuantity,
      data.author= req.body.frmProductAuthor,
      data.publisher=req.body.frmProductPublisher,
      data.status= req.body.frmProductPublished

      data.save();
        req.flash('success_msg', 'Modify Successful');
        res.redirect('/');

  })

});

// Update an existing product form action

router.get('/delete/:id', checkAdmin, function (req, res) {
  Book.remove({_id: req.params.id},function(product){
    res.redirect('/admin/product/booklist');
  });
});

module.exports = router;
function checkAdmin(req, res, next){

    if(!req.isAuthenticated()){
      next();
    }else{
      res.redirect('/admin/login');
    }
}