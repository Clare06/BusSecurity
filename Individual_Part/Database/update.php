<?php 
include_once('Include/dbConn.php');
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  exit();
}
$StdID="";
if(isset($_GET['StdID'])){
$StdID=$_GET['StdID'];		
}
$userName="";
if(isset($_GET['userName'])){
$userName=$_GET['userName'];	
}
$Address="";
if(isset($_GET['Address'])){
$Address=$_GET['Address'];	
}
$Mobile_Number="";
if(isset($_GET['Mobile'])){
$Mobile_Number=$_GET['Mobile'];	
}
$sql="UPDATE Student SET Name = '$userName' ,Address = '$Address', Mobile_Number = '$Mobile_Number' WHERE Student.StdID = $StdID;";
$result=mysqli_query($conn,$sql);
if($result){
	?>
<script>
alert("updated");
	window.location="DbUI.php";
</script>
<?php
}else{
		?>
<script>
alert("not updated");
	window.location="DbUI.php";
</script>
<?php
}







?>