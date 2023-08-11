<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">  
        <title>DbUI</title>
        <style>
        table{
            table-layout: fixed;
  width: 100%;
  border-collapse: collapse;
  border: 3px solid #074D6F;
  text-align: center;
  border-radius: 10px;
  font-family: Arial, Calibri;
        }
        td,th{
            padding: 8px;
        color:#010000 ;    
        }
        input[type=search] {
  width: 100%;
  padding: 12px 20px;
  margin: 8px 0;
  display: inline-block;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;
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
button:hover{
background-color: #51B5BF ;
}
h1{
    font-family: Arial, Calibri;
    text-align: center;
    color: #010000 ;  
}
h2{
    font-family: Arial, Calibri;
    text-align: center;
    color: #010000 ;
}
        </style>  
    </head>
    <body style="background-color: #F4F4F4;">
        <h1>Database of students</h1> <br>
        <h2>Students</h2>
<form action="DbUI.php" method="get">
<input type="search" name="sk" placeholder="Search here"/><button type="submit">Search</button>
</form>
<br>
<a href="DbUI.php"><button>All</button></a>
<br>
<?php 
include_once('Include/dbConn.php');
if (mysqli_connect_errno()) {
    echo "Failed to connect to MySQL: " . mysqli_connect_error();
    exit();
  }
  $sql="SELECT * FROM Student ";
  if(isset($_GET['sk'])){    
      $sk=$_GET['sk'];
      $sql="SELECT * FROM Student WHERE Name LIKE '%$sk%' ";
  }
  $result=mysqli_query($conn,$sql);
  $no=mysqli_num_rows($result);
  if($no>0){
	?>
    <br>
<table border="1">
	<th>Student ID</th>
	<th>Name</th>
	<th>Mobile_Number</th>
	<th>Address</th>
	<th>Update</th>
    <th>Remove</th>
	<?php
	while($row=mysqli_fetch_assoc($result)){
		?>
		<tr>
	<td><?php echo $row['StdID'];  ?></td>
	<td><?php echo $row['Name'];  ?></td>
	<td><?php echo $row['Mobile_Number'];  ?></td>
	<td><?php echo $row['Address'];  ?></td>	
	<td ><a href="editForm.php?StdID=<?php echo $row['StdID']?>"><button>Edit</button></a></td>		
	<td ><a href="delete.php?StdID=<?php echo $row['StdID'] ?>"><button>Delete</button></a></td>
	</tr>
	<?php
	}	
?>
</table>
<br>
<a href="DbForm.php"><button>ADD</button></a>
<?php
}else{	
	echo "<h1>No records</h1>";
}
?>
   <h2>RFID</h2>
<form action="DbUI.php" method="get">
<input type="search" name="skd" placeholder="Search here"/><button type="submit">Search</button>
</form>     
<?php
$sqld="SELECT * FROM RFID ";
  if(isset($_GET['skd'])){     
      $skd=$_GET['skd'];
      $sqld="SELECT * FROM RFID WHERE StdID LIKE '%$skd%' ";
  }
  $resultd=mysqli_query($conn,$sqld);
  $nod=mysqli_num_rows($resultd);
  if($nod>0){
	?>
    <br>
<table border="1">
	<th>RFID</th>
	<th>Student ID</th>
	<?php
	while($rowd=mysqli_fetch_assoc($resultd)){
		?>
		<tr>
	<td><?php echo $rowd['RFID'];  ?></td>
	<td><?php echo $rowd['StdID'];  ?></td>
	</tr>
	<?php
	}	
?>
</table>
<?php
}else{	
	echo "<h1> No records </h1>";
}
?>
    </body>
</html>