<?php 
include_once('Include/dbConn.php');
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  exit();
}
$SN="";
$MN="";
$AD="";
if(isset($_POST['SN'])){
	$SN=$_POST['SN'];
}
if(isset($_POST['MN'])){
	$MN=$_POST['MN'];
}
if(isset($_POST['AD'])){
	$AD=$_POST['AD'];
}
$sql= "INSERT INTO Student (Name, Mobile_Number, Address) VALUES ('$SN', '$MN', '$AD');";
$result=mysqli_query($conn,$sql);
?>
<?php
if($result){
	?>
<script>
alert("saved");
	window.location="Dbformd.php?MN=<?php echo $MN ?>";
</script>
<?php
}else{
		?>
<script>
alert("not saved");
	window.location="DbUI.php";
</script>
<?php
}
?>