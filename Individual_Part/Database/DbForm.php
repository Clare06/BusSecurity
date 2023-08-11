<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>BusSecurityDB</title>
        <style>
            div{ 
                box-shadow: 34px 30px 25px 0px rgba(0,0,0,0.1);
                border-radius: 25px;
                background-color: #EFFAF9;
                width: 60%;
                padding: 50px;
                font-family: "Gill Sans", sans-serif;
                font-size: 23px;
            }
input[type=text],select,[type=number] {
  width: 100%;
  padding: 12px 20px;
  margin: 8px 0;
  display: inline-block;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;
}
input[type=submit] {
  width: 100%;
  background-color: #4C92FF;
  color: white;
  padding: 14px 20px;
  margin: 8px 0;
  border: none;
  border-radius: 10px;
  cursor: pointer;
  font-size: 20px; 
}
.p{
    padding: 3px;
}
input[type=submit]:hover {
  background-color: #49CA99;
}
	#info{   
	background-color: #C0C0C0;
    border-radius: 10px;
		float:left
	}
	#data{
	float:left	
	}    
     body {
            margin: 0;
            padding-left: 20%;
        };
        #bg{
        width: 100%;
        background-color: cornsilk;};
        </style>
        <script>         
          function valmob(form){
           var mn=form.MN.value;
           const fd=String(mn)[0];
           if(fd == '0'){            
            document.getElementById('MN').value= '';
            alert("Insert number without begining in 0");
            return false;
           }else{
             return true;
           }
          }
        </script>      
    </head>
    <body >
        <h1 style="font-family: Gill Sans, sans-serif;padding-left:22%;" >BusSecurityInsert</h1>
        <form action="insert.php" method="post" style="padding: 50px;" name="form" onsubmit="return valmob(this)">
       <div >
        <span><p class="p">Student Name</p></span>
        <span><input type="text" id="SN" placeholder="Enter here" name="SN" required/></span>
        <br>
        <span><p class="p">Parent Mobile Number</p></span>
        <span><input type="number" id="MN" placeholder="Enter here" name="MN" required /></span>
        <br>
        <span><p class="p">Address</p></span>
        <span><input type="text" id="AD" placeholder="Enter here" name="AD" required/></span>
        <br>
        <br>
        <span><input type="submit" id="Sub" name="Sub"/></span>      
       </div>
        </form>     
    </body>
</html>