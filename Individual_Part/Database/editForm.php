<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Untitled Document</title>
<style>
input[type=text] {
  width: 100%;
  padding: 12px 20px;
  margin: 8px 0;
  display: inline-block;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;
}
form{
	font-family: arial,calibri;
	font-size: 20px;
}
button{
    background-color: #2396CF;
  border: none;
  color: white;
  padding: 5px 10px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  border-radius: 10px;
  width: 100px;
}
h1{
	font-family: arial,calibri;
}
button:hover{
background-color: #51B5BF ;
}
</style>
</head>
<body>
	<h1>Update Student</h1>	
	<?php 
include_once('Include/dbConn.php');
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  exit();
}
	$StdID="";
	$userName="";
	$Address="";
	$mobile_number="";	
	if(isset($_GET['StdID'])){
		$StdID=$_GET['StdID'];		
	}	
	$sql="SELECT * FROM Student WHERE StdID LIKE '%$StdID%' ";
	$result=mysqli_query($conn,$sql);
    $no=mysqli_num_rows($result);
	if($no>0){
		while($row=mysqli_fetch_assoc($result)){
         $userName=$row['Name'];
		 $Address=$row['Address'];
		 $mobile_number=$row['Mobile_Number'];
		}
	}
	?>	
<form action="update.php" method="get">	
	Name<input type="text" name="userName" value="<?php echo $userName ?>"/><br>
	Address<input type="text" name="Address" value="<?php echo $Address?>"/><br>
	Mobile Number<input type="text" name="Mobile" value="<?php echo $mobile_number ?>"/><br>
	<input type="number" name="StdID" value="<?php echo $StdID?>" hidden/><br>	
	<button type="submit">Update</button>	
</form>		
</body>
</html>