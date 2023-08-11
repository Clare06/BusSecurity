<?php 
include_once('Include/dbConn.php');
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  exit();
}
$StdID="";
if(isset($_GET['StdID'])){
$StdID=$_GET['StdID'];	
$sql="DELETE FROM Student WHERE StdID = $StdID;";	
}
$result=mysqli_query($conn,$sql);
if($result){
	?>
<script>
alert("deleted");
	window.location="DbUI.php";
</script>
<?php	
}else{	
		?>
<script>
alert("not deleted");
	window.location="DbUI.php";
</script>
<?php
}
?>