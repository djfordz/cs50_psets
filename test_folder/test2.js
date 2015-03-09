// create method to input data.
function data(username, position, profile_picture, full_name, id) {
    this.username = username;
    this.position = position;
    this.profile_picture = profile_picture;
    this.full_name = full_name;
    this.id = id;
};

// create array to hold objects
var object = new Array();

// input data.
object[0] = new data("Joe", "Accountant", "profile_image.jpg", "Joe Bloggs", "1");
object[1] = new data("Susan", "Manager", "profile_image2.jpg", "Susan Smith", "2");
object[2] = new data("David", "Janitor", "profile_image3.jpg", "David Ford", "3");
object[3] = new data("Ken", "Programmer", "profile_image4.jpg", "Ken Smith", "4");
object[4] = new data("Jennifer", "Administrative Assistant", "profile_image5.jpg", "Jennifer Lawrence", "5");



var ids = object.map(function(data) {
    return data.id;
});

//print array.
console.log(ids);


