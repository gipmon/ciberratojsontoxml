$( document ).ready(function() {
	function scroll(aid){
	    var aTag = $(aid);
	    $('html,body').animate({scrollTop: aTag.offset().top},'slow');
	}
	function load(button, filename, data){
		Downloadify.create(button,{
			filename: function(){
				return filename;
			},
			data: function(){ 
				return document.getElementById(data).value;
			},
			onComplete: function(){ alert('Your File Has Been Saved!'); },
			onCancel: function(){ alert('You have cancelled the saving of this file.'); },
			onError: function(){ alert('You must put something in the File Contents or there will be nothing to save!'); },
			swf: 'downloadify/media/downloadify.swf',
			downloadImage: 'downloadify/images/download.png',
			width: 27,
			height: 30,
			transparent: false,
			append: false
		});
	}
    $("#make").click(function(){ 
		var param = $('#param').val();
		var challenge = $('#challenge').val();
		$('#output').text('Please wait a moment!');
		$.post("api/",{param: param, challenge: challenge}, function(data){
			var response = jQuery.parseJSON(data);
			if(typeof response =='object'){
				if(response.response_type=="error"){
					$('#output').text(response.val);
  					$('#output_div').fadeOut("fast");
				}else if(response.response_type=="ok"){
					$('#grid').text(response.val.grid_xml_output);
					$('#lab').text(response.val.lab_xml_output);
					$('#param_output').text(response.val.param_xml_output);
					$('#urdf_xml_output_rotate').text(response.val.urdf_xml_output_rotate);
					$('#urdf_xml_output_fixed').text(response.val.urdf_xml_output_fixed);
					$('#output').text("OUTPUT done!");
  					$('#output_div').fadeIn("fast");
  					load("grid_save_as", "GRID.xml", "grid");
  					scroll('#output_div');
				}
			}
		});
    }); 
});