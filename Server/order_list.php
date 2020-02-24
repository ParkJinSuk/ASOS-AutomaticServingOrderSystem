<CTYPE html>
<html>
  <head>
        <meta charset="UTF-8" />
        <title>PHP MySQL load sample</title>
        <style type="text/css">
            table {
                border: 0;
                border-collapse: collapse;
                border-spacing: 0;
            }
            table td, table th {
                border: 1px solid;
                padding: 2px 5px 2px 5px;
            }
            .text-center { text-align: center; }
            .text-right { text-align: right; }
        </style>
    </head>

    <body>
        <?php
            /* Load DB */
            $conn = mysqli_connect('localhost', 'sexymandoo', 'sexymandoo', 'project');
            if ( !$conn ) die('DB Error');

            /* Set to UTF-8 Encoding */
            mysqli_query($conn, 'set session character_set_connection=utf8;');
            mysqli_query($conn, 'set session character_set_results=utf8;');
            mysqli_query($conn, 'set session character_set_client=utf8;');

            /* Load data */
            $query = 'SELECT * FROM orderDB';
            $result = mysqli_query($conn, $query);

            echo '<table class="text-center"><tr>' .
                '<th>순서</th><th>시간</th><th>테이블 번호</th><th>음식</th><th>서빙 완료</th><th>아두이노 호출</th>' .
                '</tr>';
            while( $row = mysqli_fetch_array($result) ) {
                echo '<tr><td>' . $row['_order'] . '</td>' .
                    '<td>' . $row['time'] . '</td>' .
                    '<td>' . $row['_table']. '</td>' .
                    '<td>' . $row['food'] . '</td>' .
                    '<td>' . $row['serving']. '</td>' .
                   // '<td class="text-right">' .
                    '<td>' . $row['call_arduino'] . '</td></tr>';
            }
            echo '</table>';

    



            //mysqli_close($conn);
        ?>

        <form action="<?php $_PHP_SELF ?>" method="POST">
                서빙을 원하는 테이블을 입력해주세요. <input type = "text" name = "table_num" />
                <input type = "submit" name = "submit" />
        </form>

       <?php
        $insertQuery = "update orderDB set call_arduino = 1 where _table = ".$_POST['table_num'];
        mysqli_query($conn, $insertQuery);
        //데이터가 전달되었으면 새로고침하기
    //    if ($_POST['table_num'] != NULL){
     //    echo "<meta http-equiv='refresh' content='1;finalInsertDelete.php' />";
      //  }
     
        ?>
 
    </body>
</html>


