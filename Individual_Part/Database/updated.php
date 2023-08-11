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
$RFID="";
if(isset($_GET['RFID'])){
$RFID=$_GET['RFID'];	
}
$sql="UPDATE RFID SET RFID = '$RFID'  WHERE RFID.StdID = $StdID;";
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