<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>BusSecurityDBR</title>
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
    </head>
    <body >
      <?php 
        include_once('Include/dbConn.php');
        if (mysqli_connect_errno()) {
          echo "Failed to connect to MySQL: " . mysqli_connect_error();
          exit();
        }
        $MN="";
           if(isset($_GET['MN'])){
               $MN=$_GET['MN']; }       
        $sql="SELECT * FROM Student WHERE Mobile_Number LIKE '%$MN%' ";
        $result=mysqli_query($conn,$sql);
        $no=mysqli_num_rows($result);
        ?>
        <h1 style="font-family: Gill Sans, sans-serif;padding-left:22%;" >BusSecurityInsert</h1>
        <form action="insertd.php" method="post" style="padding: 50px;">
       <div >
        <span><p class="p">RFID</p></span>
        <span><input type="text" id="RF" placeholder="Enter here" name="RF" required/></span>
        <br>
        <span><p class="p">Student ID</p></span>
        <span><select id="SI"  name="SI" required>
            <option value="">none</option>
            <?php 
            if($no>0){
              while($row=mysqli_fetch_assoc($result)){
              ?>
            <option value="<?php echo $row['StdID'] ?>"><?php echo $row['StdID'] ?></option>
             <?php
              }
            }
              ?>
        </select></span> 
        <br>
        <br>
        <span><input type="submit" id="Sub" name="Sub"/></span> 
       </div>
        </form>       
        <script src="" async defer></script>
    </body>
</html>