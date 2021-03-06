<?php

//the function getting called that will execute the update
function courier_connector_process_response($job_id)
{     
  require_once "courier_connector_mapping.inc";
  require_once "courier_connector_misc.inc";
   
  $response_parameters = file_get_contents(drupal_get_path('module', 'courier_connector_uber_7') . "/includes/" . "response_parameters.json");
  $response_parameters=json_decode($response_parameters,true);
  
  if(courier_connector_get_drupal_version() == 6) {
    $result = db_query("select response_xml, job_id, job_date, status, record_count, number_of_chunks, chunk_number from courier_responses where job_id = %d order by chunk_number desc", $job_id);
  }
  else {  
    $query = db_select("courier_responses");
    $query->fields("courier_responses", array("response_id", "response_xml", "job_id", "job_date", "status", "record_count", "number_of_chunks", "chunk_number"));
    $query->condition("courier_responses.job_id", $job_id);
    $query->condition("processed", "0", "=");
    $query->orderBy("courier_responses.chunk_number", "DESC");  

    $result = $query->execute();       
  }
  
  foreach ($result as $record) 
  {       
      $record = (array) $record;
    
      $doc = simplexml_load_string((string)$record['response_xml']);

      $method_name = (string) $doc->getName();

      //remove the _Response
      $method_name = str_replace('_Response', '', $method_name);
      
      $message = "Processing response from job id: {$record['job_id']} chunk number: {$record['chunk_number']} of {$record['number_of_chunks']}";

      if($doc->ErrorMessage != '')
      {
          $message .= " error occured. Error Message: {$doc->ErrorMessage}";
          $status = "Error";
      }
      else
      {                          
          //write the request to the request table
          $status = "True";
      }

      if(courier_connector_get_drupal_version() == 6) {
        $result = db_query("insert into courier_transaction_log (type, message, status) value('1', '%s', '%s')", $message, $status);
      }
      else { 
        //write the request to the request table
        db_insert('courier_transaction_log') 
            ->fields(array(
              'type' => 1,
              'message' => $message,
              'status' => $status
            ))
            ->execute();
      }

      //call the function
      require_once $response_parameters[COURIER_CONNECTOR_CART][$method_name]['file'];
      $response_parameters[COURIER_CONNECTOR_CART][$method_name]['method']($doc);
      
      //mark the response processed and mark a date on it
      if(courier_connector_get_drupal_version() == '6') {
        db_query("update courier_responses set processed = 1, processed_date = '%s' where response_id = %d", date( 'Y-m-d H:i:s', time()), $record['response_id']);
      }
      else {
        $query = db_update("courier_responses");
        $query->fields(array("processed" => 1, "processed_date" => date( 'Y-m-d H:i:s', time())));
        $query->condition('response_id', $record['response_id']);      
        $query->execute(); 
      }
  }

  return "done";
}
