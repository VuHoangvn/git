const express = require('express');
const router = express.Router();

const Category = require('../models/category.js');

/* GET home page. */
router.get('/category_list', checkAdmin,  function (req, res) {
	Category.find().then(function(category){
    res.render('admin/category', {category: category});
  });
});

router.get('/add-category', checkAdmin, function (req, res) {
  	res.render('admin/category_new');
});

router.post('/add-category', checkAdmin, function (req, res) {

    const category = new Category({
      name: req.body.categoryname || ' error',
    });

    category.save(function(err, result){
      req.flash('success_msg', 'Add Successful');
      res.redirect('/admin/category/category_list');
    });
  // }
});

router.get('/delete/:id', checkAdmin, function (req, res) {
  Category.remove({_id: req.params.id},function(product){
    res.redirect('/admin/category/category_list');
  });
});

router.get('/edit/:id', (req, res) => {

      res.render('admin/category_edit');

});


router.post('/edit/:id',  function (req, res) {

    Category.findOne({ _id: req.body.frmCategoryId},  function(err, data){
      data.name= req.body.categoryname,

      data.save();
        req.flash('success_msg', 'Modify Successful');
        res.redirect('/');

  })

});

router.get('/update',  function (req, res) {

    res.render('admin/category');
});

router.post('/update', checkAdmin, (req, res) => {
  Category.findOne({ _id: req.body.frmCategoryId},  function(err, data){
      if(data === null){
        res.redirect('/')
      } else {
      data.name= req.body.categoryname || 'update error!',
      

      data.save();
        req.flash('success_msg', 'Modify Successful');
        res.redirect('/admin/category/category_list');
      }
                });
  // Category.update({_id: req.body.frmCategoryId}, {$set: {name: req.body.categoryname}}, {multi: false}, (err, numReplaced) => {
  //       if(err){
  //           console.error(colors.red('Failed to update the published state: ' + err));
  //           res.status(400).json('Published state not updated');
  //       }else{

  //           res.redirect('/admin/category/category_list');
  //       }
  //   });
});

module.exports = router;
function checkAdmin(req, res, next){

    if(!req.isAuthenticated()){
      next();
    }else{
      res.redirect('/admin/login');
    }
}