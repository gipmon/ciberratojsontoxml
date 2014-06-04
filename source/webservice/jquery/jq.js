$( document ).ready(function() {
    $("#make").click(function(){ 
		var param = $('#param').val();
		var challange = $('#challange').val();
		console.log("LOL");
		$('#output').text('Please wait a moment!');
		$.post("compiling.php",{param: param, challange: challange}, function(data){
			$('#output').text(data);
		});
    }); 
});