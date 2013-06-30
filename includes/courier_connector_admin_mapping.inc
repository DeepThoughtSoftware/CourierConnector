<?php

/**
 * Builds the conifg form.
 */
function courier_connector_mapping_form($form, &$form_state) {
 
  $current_tab = '';
  
  // Respond to AJAX-triggger:
  // Add new row
  if ($form_state['method'] == "post" && sizeof($form_state['input']) > 0) {
    //determine which tab was selected
    $tab = '';  
    if(isset($form_state['input']['add_request_row'])) {
      $tab = $form_state['input']['request_mapping_settings__active_tab'];
    }
    else if(isset($form_state['input']['add_response_row'])) {
      $tab = $form_state['input']['response_mapping_settings__active_tab'];
    }
    
    if($tab != '') {
      //create a new blank row in the database to hold this mapping    
      preg_match("/edit-courier-mapping-from-(.*?)-/", $tab, $request_type);

      $current_tab = $request_type[1];

      if(sizeof($request_type)> 0) {    
        if(isset($form_state['input']['add_request_row'])) {         
          db_insert("courier_mapping_from_{$request_type[1]}_request")
            ->fields(array("to_{$request_type[1]}_request_field_id" => 1, 'from_field' => ''))
            ->execute();
        }
        else if(isset($form_state['input']['add_response_row'])) {        
          db_insert("courier_mapping_from_{$request_type[1]}_response")
            ->fields(array("to_{$request_type[1]}_response_field_id" => 1, 'from_field' => ''))
            ->execute();
        }      
      }
    }
  }
  
  // Put fieldsets into vertical tabs
  $form['request_mapping_settings'] = array(
        '#type' => 'vertical_tabs',
        '#default_tab' => 'edit-' . $current_tab
      );  
  $form['response_mapping_settings'] = array('#type' => 'vertical_tabs');  

  $form['notification'] = array(    
    '#weight' => -99,      
    '#markup' => "Requests sent to QuickBooks"
  );
  
  
  $form['notification_1'] = array(    
    '#weight' => 0,      
    '#markup' => "Responses from QuickBooks"
  );
  
  courier_connector_mapping_add_tabs($form, $form_state, 'request');
  courier_connector_mapping_add_tabs($form, $form_state, 'response');
  
  $form['save_mapping']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Mapping'),
  );
  
  return $form;
}

function courier_connector_mapping_form_submit($form, &$form_state) { 
  if ($form_state['method'] == "post" && sizeof($form_state['values']) > 0) {
    if(isset($form_state['values']['submit']) && $form_state['input']['op'] === 'Save Mapping') {
      //save the field settings
      //should be an update only affair, inserts are done when add row is done
      foreach($form_state['input'] as $command => $fields) {
        //match the commands we care about, start with courier_mapping_        
        if(!strncmp($command, "courier_mapping_", strlen("courier_mapping_"))) {                
          preg_match("/courier_mapping_from_(.*?)_(.*)/", $command, $request_name);          
          foreach($fields['from_field'] as $id => $value) {                        
            $query = db_update($command);                                    
            $query->fields(array(
                'from_field' => $fields['from_field'][$id],
                "to_{$request_name[1]}_{$request_name[2]}_field_id" => $fields['to_field'][$id],
                'from_alternative' => ($fields['from_alternative'][$id] == '' ? null : $fields['from_alternative'][$id]),
                'sort_order' => $fields['sort_order'][$id],
                'commands' => $fields['commands'][$id]
            ));
            $query->condition("from_{$request_name[1]}_{$request_name[2]}_field_id", $id);
            $query->execute();                          
          }
        }
      }
    }
  }
  
  drupal_set_message("Mapping Saved");
}

function courier_connector_mapping_add_tabs(&$form, &$form_state, $type) {
  global $db_url;
  
  $db_name = ltrim(trim(parse_url($db_url, PHP_URL_PATH)), "/" );
  
  //get a name of all of the mappings
  $tables = db_query("SELECT table_name FROM INFORMATION_SCHEMA.TABLES where table_name like 'courier_mapping_from_%_{$type}' and TABLE_SCHEMA = '{$db_name}'");
  
  //loop the available table names and handle them accordingly
  foreach($tables as $table) {
    
    //sift out the name of the request    
    preg_match("/courier_mapping_from_(.*?)_{$type}/", $table->table_name, $request_name);
   
    if(sizeof($request_name)> 0) {    
      $form["{$type}_mapping_settings"][$table->table_name] = array(
        '#type' => 'fieldset',
        '#title' => t($request_name[1]),
        '#group' => "{$type}_mapping_settings",
        '#weight' => 0,      
        '#theme' => "courier_connector_admin_{$type}_mapping_table",
        '#tree' => TRUE,  
      );
               
      $from_id = "from_{$request_name[1]}_{$type}_field_id";
      $to_id = "to_{$request_name[1]}_{$type}_field_id";
      
      $from_fields = db_query("select * from {$table->table_name}");
      $to_fields = db_select("courier_mapping_to_{$request_name[1]}_{$type}")
                    ->fields("courier_mapping_to_{$request_name[1]}_{$type}", array("to_field", "to_{$request_name[1]}_{$type}_field_id"))
                    ->execute();
        
      $to_field_data = array();
      foreach($to_fields as $to_field) {
        $to_field_data[(string)"{$to_field->$to_id}"] = $to_field->to_field;
      }
   
      foreach($from_fields as $from_field) {        
        $form["{$type}_mapping_settings"][$table->table_name]['from_field'][$from_field->$from_id] = array(
              '#type' => 'textfield',              
              '#value' => $from_field->from_field);
                          
        $form["{$type}_mapping_settings"][$table->table_name]['to_field'][$from_field->$from_id] = array(
              '#type' => 'select',
              '#options' => $to_field_data,                            
              '#value' => (string)"{$from_field->$to_id}"
            );
        
        $form["{$type}_mapping_settings"][$table->table_name]['from_alternative'][$from_field->$from_id] = array(    
              '#type' => 'textfield', 
              '#size' => 20,
              '#value' => $from_field->from_alternative,
            );
        $form["{$type}_mapping_settings"][$table->table_name]['sort_order'][$from_field->$from_id] = array(
              '#type' => 'select',
              '#options' => array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
            );
        $form["{$type}_mapping_settings"][$table->table_name]['commands'][$from_field->$from_id] = array(    
              '#type' => 'textfield',    
              '#size' => 20,
              '#value' => $from_field->commands,
            );                
      }
    }
    
    $form["{$type}_mapping_settings"]['add_row'] = array (
      '#type' => 'submit',      
      '#group' => "{$type}_mapping_settings",
      '#value' => t("Add Row"),
      '#name' => "add_{$type}_row",
//      '#ajax' => array(
//          'callback' => 'courier_connector_mapping_add_row_callback',
//          'wrapper' => 'request_mapping_settings',
//          'method' => 'replace',
//          'effect' => 'fade'
//      )
    );
  }
}

function theme_courier_connector_admin_request_mapping_table($form)
{  
  return courier_connector_admin_request_get_mapping_table($form, true);
}

function theme_courier_connector_admin_response_mapping_table($form)
{  
  return courier_connector_admin_request_get_mapping_table($form);
}

function courier_connector_admin_request_get_mapping_table($form, $request = false) {
   if(courier_connector_get_drupal_version() == '7') {
    $form = $form['form'];
  }
  
  $rows = array();

  if($request) {
    $header = array(t('Cart Field'), t('QuickBooks Field'), t('Alt Cart Field'), t('Sort Order'), t('From field commands'));
  }
  else {
    $header = array(t('QuickBooks Field'), t('Cart Field'), t('Alt QuickBooks Field'), t('Sort Order'), t('From field commands'));
  }

  foreach (element_children($form['from_field']) as $key) {     
    $rows[] = array(
       drupal_render($form['from_field'][$key]),
       drupal_render($form['to_field'][$key]),
       drupal_render($form['from_alternative'][$key]),                
       drupal_render($form['sort_order'][$key]),               
       drupal_render($form['commands'][$key]),       
     );             
   } 

   if(courier_connector_get_drupal_version() == '6') {
     $output = theme('table', $header, $rows);
   }
   else {
     $output = theme('table', array(
         'header' => $header,
         'rows' => $rows
     ));
   }

   return $output;
}
