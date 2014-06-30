<?php

require_once 'courier_connector_rest_server.inc';

function get_courier_menu() {  
  $items = array();

//  $items['courier/update'] = array(    
//    'page callback' => 'courier_update', 
//    'access arguments' => array('access content'),
//    'type' => MENU_CALLBACK,
//    'file' => 'includes/update.inc',
//  );
//  
//   $items['courier/update.php'] = array(    
//    'page callback' => 'courier_update', 
//    'access arguments' => array('access content'),
//    'type' => MENU_CALLBACK,
//    'file' => 'includes/update.inc',
//  );
//  
//  
//  $items['courier/generate_request'] = array(    
//    'page callback' => 'generate_request', 
//    'access arguments' => array('access content'),
//    'type' => MENU_CALLBACK,
//    'file' => 'includes/request_handler.inc',
//  );   
//  
//  $items['admin/config/courier'] = array(    
//    'title' => 'Courier Settings',
//    'page callback' => 'drupal_get_form', 
//    'page arguments' => array('courier_connector_admin'),
//    'access arguments' => array('access content'),
//    'type' => MENU_CALLBACK,
//    'file' => 'includes/admin.inc',
//  );
//  
//  $items['admin/config/courier/mapping/product'] = array( 
//    'title' => 'Courier Product Mapping',
//    'page callback' => 'courier_connector_admin_mapping_product', 
//    'access arguments' => array('access content'),
//    'type' => MENU_CALLBACK,
//    'file' => 'includes/admin_mapping.inc',
//  );
//  
//  $items['admin/config/courier/mapping/customer'] = array(    
//    'title' => 'Courier User Mapping',
//    'page callback' => 'courier_connector_admin_mapping_user', 
//    'access arguments' => array('access content'),
//    'type' => MENU_CALLBACK,
//    'file' => 'includes/admin_mapping.inc',
//  );
//  
//  $items['admin/config/courier/request'] = array(    
//    'title' => 'Courier Requests',
//    'page callback' => 'drupal_get_form', 
//    'page arguments' => array('courier_connector_admin_requests'),
//    'access arguments' => array('access content'),
//    'type' => MENU_CALLBACK,
//    'file' => 'includes/admin_requests.inc',
//  );
//  
//   $items['courier'] = array(    
//    'title' => '',
//    'page callback' => 'courier_connector_courier_ws',     
//    'access arguments' => array('access content'),
//    'type' => MENU_CALLBACK,
//    'file' => 'includes/webservice/courier_ws.php',
//  );
  $items['admin/store/integration'] = array(
    'title' => 'QuickBooks Integration',
    'description' => 'Administer your QuickBooks Integration.',
    'page callback' => 'system_admin_menu_block_page',
    'access arguments' => array('access administration pages'),
    'file path' => drupal_get_path('module', 'system'),
    'file' => 'system.admin.inc',
    'weight' => -7,
  );
  
  $items['admin/store/integration/config'] = array(
    'title' => 'Configuration',
    'description' => 'Configure settings for your QuickBooks Integration.',
    'page callback' => 'drupal_get_form',
    'access arguments' => array('access administration pages'),    
    'type' => MENU_NORMAL_ITEM,
    'weight' => 50,
    'file' => 'includes/courier_connector_admin_config.inc',
  );
  
  if(courier_connector_get_drupal_version() == 6) {
    $items['admin/store/integration/config']['page arguments'] = array('courier_connector_config_form_6');
  }
  else {
    $items['admin/store/integration/config']['page arguments'] = array('courier_connector_config_form');
  }
  
  
  $items['admin/store/integration/log'] = array(
    'title' => 'Logs',
    'description' => 'Communication logs.',
    'page callback' => 'drupal_get_form',
    'access arguments' => array('access administration pages'),    
    'type' => MENU_NORMAL_ITEM,
    'weight' => 50,    
    'file' => 'includes/courier_connector_admin_log.inc',
  );
  
  if(courier_connector_get_drupal_version() == 6) {
    $items['admin/store/integration/log']['page arguments'] = array('courier_connector_logs_form_6');
  }
  else {
    $items['admin/store/integration/log']['page arguments'] = array('courier_connector_logs_form');
  }
  
  $items['admin/store/integration/mapping'] = array(
    'title' => 'Field Mappings for the integration.',
    'description' => 'Integration Mappings.',
    'page callback' => 'drupal_get_form',
    'access arguments' => array('access administration pages'),
    'page arguments' => array('courier_connector_mapping_form'),
    'type' => MENU_NORMAL_ITEM,
    'weight' => 50,
    'file' => 'includes/courier_connector_admin_mapping.inc',
  );
  
//  $items['admin/store/integration/command_queue'] = array(
//    'title' => 'Queue Command',
//    'description' => 'Queue commands to be processed by the integration.',
//    'page callback' => 'drupal_get_form',
//    'page arguments' => array('courier_connector_queue_form'),
//    'access arguments' => array('access administration pages'),
//    'type' => MENU_NORMAL_ITEM,
//    'weight' => 50,
//    'file' => 'includes/courier_connector_admin_queue.inc',
//  );
  
//  $items['courier_connector/update'] = array(    
//    'page callback' => 'courier_connector_courier_update', 
//    'access arguments' => array('access content'),
//    'type' => MENU_CALLBACK,
//    'file' => 'includes/courier_connector_update.inc',
//  );
//  
//  $items['courier_connector/generate_request'] = array(    
//    'page callback' => 'courier_connector_generate_request', 
//    'access arguments' => array('access content'),
//    'type' => MENU_CALLBACK,
//    'file' => 'includes/courier_connector_request_handler.inc',
//  );   
  return $items;
}

//custom rules exposed
function get_courier_connector_rules_action_info() {
//  $actions['add_item'] = array(
//    'arguments' => array(          
//      'item_ids' => array(
//        'type' => 'text',
//        'label' => t('Comma seperated list of Item ids to download'),
//        'save' => true
//      ),
//    ),
//    'label' => t('Download item(s) into Quickbooks'),    
//    'base' => 'courier_connector_download_items',  
//  );
      
  $actions['read_items'] = array(
    'arguments' => array(          
      'date_modified' => array(
        'type' => 'date',
        'label' => t('From Modified Date'),
        'save' => true
      ),
    ),
    'label' => t('Read item(s) from Quickbooks'),    
    'base' => 'courier_connector_read_items',  
  );
  
  $actions['read_items_cycle'] = array(    
    'label' => t('Read item(s) from Quickbooks Cycle'),    
    'base' => 'courier_connector_read_items_cycle',  
  );
  
//  $actions['read_customers'] = array(
//    'arguments' => array(          
//      'date_modified' => array(
//        'type' => 'date',
//        'label' => t('From Modified Date'),
//        'save' => true
//      ),
//    ),
//    'label' => t('Read customers from Quickbooks'),    
//    'base' => 'courier_connector_read_customers',  
//  );
  
   $actions['add_order'] = array(
    'parameter' => array(
       'order' => array(
         'type' => 'commerce_order',
         'label' => t('Order'),
         'save' => TRUE,
       ),       
     ),    
    'label' => t('Send order to Quickbooks'),    
    'base' => 'courier_connector_download_order',  
  );       
  
  if(courier_connector_get_drupal_version() == "6") {
   // $actions['add_item']['module'] = "Courier Connector";
    $actions['read_items']['module'] = "Courier Connector";
  //  $actions['read_customers']['module'] = "Courier Connector";
    $actions['add_order']['module'] = "Courier Connector";    
  }
  else {
  //  $actions['add_item']['group'] = "Courier Connector";
    $actions['read_items']['group'] = "Courier Connector";
  //  $actions['read_customers']['group'] = "Courier Connector";
    $actions['add_order']['group'] = "Courier Connector";
  }   
  return $actions;
}

function get_courier_connector_services_resources() {
 return array(
  'CourierConnector' => array(          
    'index' => array(
      'help' => 'Retrieves open requests, if the job_id is passed will call the processing of that job response',      
      'file' => array('type' => 'inc', 'module' => 'courier_connector_uber_7', 'name' => 'includes/courier_connector_retrieve_requests'),      
      'callback' => 'courier_connector_retrieve_requests',
      'access callback' => 'courier_connector_access',
      'access arguments' => array('view'),
      'access arguments append' => TRUE,
      'args' => array(          
      ),
    ),   
    'update' => array(
      'help' => 'Create a response to a request',      
      'file' => array('type' => 'inc', 'module' => 'courier_connector_uber_7', 'name' => 'includes/courier_connector_create_responses'),      
      'callback' => 'courier_connector_create_responses',
      'access callback' => 'courier_connector_access',
      'access arguments' => array('create'),
      'access arguments append' => TRUE,
      'args' => array( 
        array(
               'name' => 'response_xml',
               'optional' => FALSE,
               'source' => 'data',
               'description' => '',
               'type' => 'text',
             ), 
        array(
               'name' => 'job_id',
               'optional' => FALSE,
               'source' => array('path' => '0'),
               'description' => '',
               'type' => 'int',
             ),
        array(
               'name' => 'job_date',
               'optional' => FALSE,
               'source' => array('path' => '1'),
               'description' => '',
               'type' => 'text',
             ),          
        array(
               'name' => 'status',
               'optional' => FALSE,
               'source' => array('path' => '2'),
               'description' => '',
               'type' => 'text',
             ),
        array(
               'name' => 'record_count',
               'optional' => FALSE,
               'source' => array('path' => '3'),
               'description' => '',
               'type' => 'text',
             ),
        array(
               'name' => 'number_of_chunks',
               'optional' => FALSE,
               'source' => array('path' => '4'),
               'description' => '',
               'type' => 'int',
             ),
        array(
               'name' => 'chunk_number',
               'optional' => FALSE,
               'source' => array('path' => '5'),
               'description' => '',
               'type' => 'int',
             ),
      ),
    ),            
  ),
 );
}

function get_courier_connector_rest_server_request_parsers_alter(&$parsers) {
  $parsers['text/xml'] = "CourierXMLResponseParser";
}
 

function get_courier_connector_rest_server_response_formatters_alter(&$formatters) {
  $formatters['xml']['view'] = 'RESTServerViewCourier';
}

/**
  * Implements hook_permission().
  */
function get_courier_connector_permission() {
 return array(
     'get courier connector requests' => array(
      'title' => t('Get Open courier connector Requests'), 
      'description' => t('Get any requests that have yet to be processed by courier connector'),
     ),
     'create courier connector responses' => array(
      'title' => t('Create the response from courier connector requests'), 
      'description' => t('Create the response record from the courier connector request')     
     ),    
 );
}

/**
* Access callback for the get requests resource.
*
* @param string $op
*  The operation that's going to be performed.
* @param array $args
*  The arguments that will be passed to the callback.
* @return bool
*  Whether access is given or not.
*/
function courier_connector_access($op, $args) {
 global $user;
 $access = true;

 switch ($op) {
   case 'view':     
     $access = user_access('get courier connector requests');     
     break;
   case 'create':     
     $access = user_access('create courier connector responses');     
     break;
 }
 $access = true;
 return $access;
}

function get_courier_connector_theme($existing, $type, $theme, $path) {
    $theme_hooks = array(
        'courier_connector_request_table' => array(
          'render element' => 'form',
          'file' => 'includes/courier_connector_admin_queue.inc',
        ), 
        'courier_connector_admin_request_mapping_table' => array(
          'render element' => 'form',
          'file' => 'includes/courier_connector_admin_mapping.inc',
        ), 
       'courier_connector_admin_response_mapping_table' => array(
          'render element' => 'form',
          'file' => 'includes/courier_connector_admin_mapping.inc',
        ), 
//        'courier_connector_order_table' => array(
//           'render element' => 'form',
//           'file' => 'includes/admin_requests.inc',
//        ),
//        'courier_connector_product_table' => array(
//           'render element' => 'form',
//           'file' => 'includes/admin_requests.inc',
//        ),
//        'courier_connector_customer_table' => array(
//           'render element' => 'form',
//           'file' => 'includes/admin_requests.inc',
//        ),
//         'courier_connector_order_mapping_table' => array(
//       'render element' => 'form',
//       'file' => 'includes/admin.inc',
//        ),
//        'courier_connector_request_table' => array(
//       'render element' => 'form',
//       'file' => 'includes/admin_requests.inc',
//        ),
       'courier_connector_request_log_table' => array(
         'render element' => 'form',
         'file' => 'includes/courier_connector_admin_log.inc',
        ),
//        'courier_connector_customer_mapping_table' => array(
//       'render element' => 'form',
//       'file' => 'includes/admin.inc',
//        )  
        
//        'courier_connector_order_table' => array(
//           'render element' => 'form',
//           'file' => 'includes/admin_requests.inc',
//        ),
//        'courier_connector_product_table' => array(
//           'render element' => 'form',
//           'file' => 'includes/admin_requests.inc',
//        ),
//        'courier_connector_customer_table' => array(
//           'render element' => 'form',
//           'file' => 'includes/admin_requests.inc',
//        ),
//         'courier_connector_order_mapping_table' => array(
//       'render element' => 'form',
//       'file' => 'includes/admin.inc',
//        ),
//        'courier_connector_request_table' => array(
//       'render element' => 'form',
//       'file' => 'includes/admin_requests.inc',
//        ),
//       'courier_connector_request_log_table' => array(
//       'render element' => 'form',
//       'file' => 'includes/admin_requests.inc',
//        ),
//        'courier_connector_customer_mapping_table' => array(
//       'render element' => 'form',
//       'file' => 'includes/admin.inc',
//        )
    );
            
    return $theme_hooks;
}

function courier_connector_get_drupal_version() {
  preg_match("/(.*?)\.../", VERSION, $matches);
  
  if(is_array($matches))  
    return $matches[1];
  
  return 6;
}

function courier_connector_install_default_mapping() {
 db_query("INSERT INTO `courier_mapping_from_customer_request` (`from_customer_request_field_id`, `to_customer_request_field_id`, `from_field`, `from_alternative`, `sort_order`, `commands`) VALUES
            (1, 7, 'commerce_customer_address:und:0:name_line', NULL, 0, 'explode( ,0)'),
            (2, 13, 'commerce_customer_address:und:0:name_line', ' ', 0, 'explode( ,1)'),
            (3, 23, 'commerce_customer_address:und:0:locality', NULL, 0, NULL),
            (4, 24, 'commerce_customer_address:und:0:country', NULL, 0, NULL),
            (5, 25, 'commerce_customer_address:und:0:postal_code', NULL, 0, NULL),
            (6, 26, 'commerce_customer_address:und:0:administrative_area', NULL, 0, NULL),
            (7, 27, 'commerce_customer_address:und:0:thoroughfare', NULL, 0, NULL),
            (8, 5, 'mail', NULL, 0, NULL),
            (9, 2, 'uid', NULL, 0, NULL),
            (19, 1, 'field_quickbooks_id:und:0:value', NULL, 0, NULL),
            (20, 1, '', NULL, 0, NULL),
            (21, 1, '', NULL, 0, NULL);");
 
 db_query("INSERT INTO `courier_mapping_from_customer_response` (`from_customer_response_field_id`, `to_customer_response_field_id`, `from_field`, `from_alternative`, `sort_order`, `commands`) VALUES
            (1, 6, 'BillingState', NULL, 0, NULL),
            (2, 4, 'BillingCountry', NULL, 0, NULL),
            (3, 3, 'BillingCity', NULL, 0, NULL),
            (4, 1, 'FirstName', NULL, 0, 'append( )'),
            (5, 1, 'LastName', NULL, 0, NULL),
            (6, 5, 'BillingPostalCode', NULL, 0, NULL),
            (7, 7, 'BillingStreet', NULL, 0, NULL),
            (8, 10, 'CustomerID', NULL, 0, NULL),
            (9, 8, 'EMail', NULL, 0, NULL),
            (10, 9, 'RelatedID', NULL, 0, NULL);");
 
 db_query("INSERT INTO `courier_mapping_from_inventoryitem_request` (`from_inventoryitem_request_field_id`, `to_inventoryitem_request_field_id`, `from_field`, `from_alternative`, `sort_order`, `commands`) VALUES
            (1, 1, 'title', NULL, 0, NULL),
            (3, 4, 'commerce_price:und:0:amount', NULL, 0, 'divide(100)'),
            (6, 10, 'sku', NULL, 0, NULL),
            (7, 17, 'product_id', NULL, 0, NULL),
            (11, 1, '', NULL, 0, NULL),
            (12, 1, '', NULL, 0, NULL);");
 
 db_query("INSERT INTO `courier_mapping_from_iteminventory_request` (`from_iteminventory_request_field_id`, `to_iteminventory_request_field_id`, `from_field`, `from_alternative`, `sort_order`, `commands`) VALUES
            (1, 1, 'title', NULL, 0, NULL),
            (3, 4, 'commerce_price:und:0:amount', NULL, 0, 'divide(100)'),
            (6, 10, 'sku', NULL, 0, NULL),
            (7, 17, 'product_id', NULL, 0, NULL);");

 db_query("INSERT INTO `courier_mapping_from_iteminventory_response` (`from_iteminventory_response_field_id`, `to_iteminventory_response_field_id`, `from_field`, `from_alternative`, `sort_order`, `commands`) VALUES
            (1, 3, 'Price1', NULL, 0, NULL),
            (2, 1, 'ALU', NULL, 0, NULL),
            (3, 6, 'OnHandStore01', NULL, 0, NULL),
            (4, 2, 'Desc1', NULL, 0, NULL),
            (5, 7, 'DepartmentCode', NULL, 0, NULL);");
 
 db_query("INSERT INTO `courier_mapping_from_salesorderitem_request` (`from_salesorderitem_request_field_id`, `to_salesorderitem_request_field_id`, `from_field`, `from_alternative`, `sort_order`, `commands`) VALUES
            (1, 1, 'field_quickbooks_id:und:0:value', NULL, 0, NULL),
            (2, 13, 'commerce_unit_price:und:0:amount', NULL, 0, 'divide(100)'),
            (4, 14, 'quantity', NULL, 0, NULL);");
 
 db_query("INSERT INTO `courier_mapping_from_salesorder_request` (`from_salesorder_request_field_id`, `to_salesorder_request_field_id`, `from_field`, `from_alternative`, `sort_order`, `commands`) VALUES
            (1, 2, 'order_id', NULL, 0, NULL),
            (2, 13, 'created', NULL, 0, 'date(Y-m-d H:i:s)'),
            (3, 28, 'commerce_customer_address:und:0:locality', NULL, 0, NULL),
            (4, 30, 'commerce_customer_address:und:0:country', NULL, 0, NULL),
            (5, 31, 'commerce_customer_address:und:0:name_line', NULL, 0, NULL),
            (6, 36, 'commerce_customer_address:und:0:postal_code', NULL, 0, NULL),
            (7, 39, 'commerce_customer_address:und:0:administrative_area', NULL, 0, NULL),
            (8, 40, 'commerce_customer_address:und:0:thoroughfare', NULL, 0, NULL),
            (9, 41, 'commerce_customer_address:und:0:premise', NULL, 0, NULL),
            (10, 15, 'commerce_customer_address:und:0:locality', NULL, 0, NULL),
            (11, 17, 'commerce_customer_address:und:0:country', NULL, 0, NULL),
            (12, 18, 'commerce_customer_address:und:0:name_line', NULL, 0, NULL),
            (13, 23, 'commerce_customer_address:und:0:postal_code', NULL, 0, NULL),
            (14, 24, 'commerce_customer_address:und:0:administrative_area', NULL, 0, NULL),
            (15, 25, 'commerce_customer_address:und:0:thoroughfare', NULL, 0, NULL),
            (16, 26, 'commerce_customer_address:und:0:premise', NULL, 0, NULL),
            (17, 1, 'field_quickbooks_id:und:0:value', NULL, 0, NULL),
            (18, 42, 'uid', NULL, 0, NULL);");
 
 db_query("INSERT INTO `courier_mapping_to_customer_request` (`to_customer_request_field_id`, `to_field`, `default_value`, `commands`) VALUES
            (1, 'CustomerID', NULL, NULL),
            (2, 'RelatedID', NULL, NULL),
            (3, 'CustomerDiscountPercent', '0', NULL),
            (4, 'CustomerType', NULL, NULL),
            (5, 'EMail', NULL, NULL),
            (6, 'IsOkToEMail', 'false', NULL),
            (7, 'FirstName', NULL, NULL),
            (8, 'IsAcceptingChecks', 'false', NULL),
            (9, 'IsUsingChargeAccount', 'false', NULL),
            (10, 'IsUsingWithQB', 'false', NULL),
            (11, 'IsRewardsMember', 'false', NULL),
            (12, 'IsNoShipToBilling', 'false', NULL),
            (13, 'LastName', NULL, NULL),
            (14, 'Notes', NULL, NULL),
            (15, 'Phone', NULL, NULL),
            (16, 'Phone2', NULL, NULL),
            (17, 'Phone3', NULL, NULL),
            (18, 'Phone4', NULL, NULL),
            (19, 'PriceLevelNumber', NULL, NULL),
            (20, 'Salutation', NULL, NULL),
            (21, 'TaxCategory', NULL, NULL),
            (22, 'BillingCompanyName', NULL, NULL),
            (23, 'BillingCity', NULL, NULL),
            (24, 'BillingCountry', NULL, NULL),
            (25, 'BillingPostalCode', NULL, NULL),
            (26, 'BillingState', NULL, NULL),
            (27, 'BillingStreet', NULL, NULL),
            (28, 'BillingStreet2', NULL, NULL),
            (29, 'DefaultShipAddress', NULL, NULL),
            (30, 'ShippingAddressName', NULL, NULL),
            (31, 'ShippingCompanyName', NULL, NULL),
            (32, 'ShippingFullName', NULL, NULL),
            (33, 'ShippingCity', NULL, NULL),
            (34, 'ShippingCountry', NULL, NULL),
            (35, 'ShippingPostalCode', NULL, NULL),
            (36, 'ShippingState', NULL, NULL),
            (37, 'ShippingStreet', NULL, NULL),
            (38, 'ShippingStreet2', NULL, NULL);");
 
 db_query("INSERT INTO `courier_mapping_to_customer_response` (`to_customer_response_field_id`, `to_field`, `default_value`, `commands`) VALUES
            (1, 'commerce_customer_address:und:0:name_line', NULL, NULL),
            (3, 'commerce_customer_address:und:0:locality', NULL, NULL),
            (4, 'commerce_customer_address:und:0:country', NULL, NULL),
            (5, 'commerce_customer_address:und:0:postal_code', NULL, NULL),
            (6, 'commerce_customer_address:und:0:administrative_area', NULL, NULL),
            (7, 'commerce_customer_address:und:0:thoroughfare', NULL, NULL),
            (8, 'mail', NULL, NULL),
            (9, 'uid', NULL, NULL),
            (10, 'field_quickbooks_id:und:0:value', NULL, NULL);");
 
 db_query("INSERT INTO `courier_mapping_to_inventoryitem_request` (`to_inventoryitem_request_field_id`, `to_field`, `default_value`, `commands`, `active`) VALUES
            (1, 'Desc1', NULL, NULL, NULL),
            (2, 'Desc2', NULL, NULL, NULL),
            (3, 'UPC', NULL, NULL, NULL),
            (4, 'Price1', NULL, NULL, NULL),
            (5, 'Price2', NULL, NULL, NULL),
            (6, 'Price3', NULL, NULL, NULL),
            (7, 'Price4', NULL, NULL, NULL),
            (8, 'DepartmentCode', NULL, NULL, NULL),
            (9, 'ItemNumber', NULL, NULL, NULL),
            (10, 'ALU', NULL, NULL, NULL),
            (11, 'Cost', NULL, NULL, NULL),
            (12, 'Attribute', NULL, NULL, NULL),
            (13, 'MSRP', NULL, NULL, NULL),
            (14, 'Size', NULL, NULL, NULL),
            (15, 'Manufacturer', NULL, NULL, NULL),
            (16, 'OnHandStore01', NULL, NULL, NULL),
            (17, 'RelatedID', NULL, NULL, NULL);");
 
 db_query("INSERT INTO `courier_mapping_to_inventoryitem_response` (`to_inventoryitem_response_field_id`, `to_field`, `default_value`, `commands`) VALUES
            (1, 'sku', NULL, NULL),
            (2, 'title', NULL, NULL),
            (3, 'commerce_price', NULL, NULL),
            (4, 'status', NULL, NULL),
            (5, 'field_images', NULL, NULL);");
 
 db_query("INSERT INTO `courier_mapping_to_iteminventory_request` (`to_iteminventory_request_field_id`, `to_field`, `default_value`, `commands`, `active`) VALUES
            (1, 'Desc1', NULL, NULL, NULL),
            (2, 'Desc2', NULL, NULL, NULL),
            (3, 'UPC', NULL, NULL, NULL),
            (4, 'Price1', NULL, NULL, NULL),
            (5, 'Price2', NULL, NULL, NULL),
            (6, 'Price3', NULL, NULL, NULL),
            (7, 'Price4', NULL, NULL, NULL),
            (8, 'DepartmentCode', 'SYS', NULL, NULL),
            (9, 'ItemNumber', NULL, NULL, NULL),
            (10, 'ALU', NULL, NULL, NULL),
            (11, 'Cost', NULL, NULL, NULL),
            (12, 'Attribute', NULL, NULL, NULL),
            (13, 'MSRP', NULL, NULL, NULL),
            (14, 'Size', NULL, NULL, NULL),
            (15, 'Manufacturer', NULL, NULL, NULL),
            (16, 'OnHandStore01', NULL, NULL, NULL),
            (17, 'RelatedID', NULL, NULL, NULL);");
 
 db_query("INSERT INTO `courier_mapping_to_iteminventory_response` (`to_iteminventory_response_field_id`, `to_field`, `default_value`, `commands`) VALUES
            (1, 'sku', 'test', NULL),
            (2, 'title', NULL, NULL),
            (3, 'commerce_price', NULL, NULL),
            (4, 'status', NULL, NULL),
            (5, 'field_images', NULL, NULL),
            (6, 'commerce_stock', NULL, NULL),
            (7, 'field_department', NULL, NULL);");
 
db_query("INSERT INTO `courier_mapping_to_salesorderitem_request` (`to_salesorderitem_request_field_id`, `to_field`, `default_value`, `commands`) VALUES
            (1, 'ItemID', NULL, NULL),
            (2, 'SalesOrderLineItemID', NULL, NULL),
            (3, 'ALU', NULL, NULL),
            (4, 'Associate', NULL, NULL),
            (5, 'Attribute', NULL, NULL),
            (6, 'Commision', NULL, NULL),
            (7, 'Desc1', NULL, NULL),
            (8, 'Desc2', NULL, NULL),
            (9, 'Discount', NULL, NULL),
            (10, 'DiscountPercent', NULL, NULL),
            (11, 'DiscountType', NULL, NULL),
            (12, 'ExtendedPrice', NULL, NULL),
            (13, 'Price', NULL, NULL),
            (14, 'Qty', NULL, NULL),
            (15, 'SerialNumber', NULL, NULL),
            (16, 'Size', NULL, NULL),
            (17, 'TaxCode', NULL, NULL),
            (18, 'UnitOfMeasure', NULL, NULL),
            (19, 'UPC', NULL, NULL),
            (20, 'DiscountSource', NULL, NULL),
            (21, 'ExtendedTax', NULL, NULL),
            (22, 'NumberOfBaseUnits', NULL, NULL),
            (23, 'PriceLevelNumber', NULL, NULL),
            (24, 'QtySold', NULL, NULL),
            (25, 'TaxAmount', NULL, NULL),
            (26, 'TaxPercentage', NULL, NULL),
            (27, 'Weight', NULL, NULL),
            (28, 'WebDesc', NULL, NULL),
            (29, 'Manufacturer', NULL, NULL),
            (30, 'WebSKU', NULL, NULL),
            (31, 'ItemNumber', NULL, NULL);");

db_query("INSERT INTO `courier_mapping_to_salesorder_request` (`to_salesorder_request_field_id`, `to_field`, `default_value`, `commands`) VALUES
            (1, 'SalesOrderID', NULL, NULL),
            (2, 'RelatedID', NULL, NULL),
            (3, 'Associate', NULL, NULL),
            (4, 'Cashier', NULL, NULL),
            (5, 'CustomerID', NULL, NULL),
            (6, 'Discount', '0', NULL),
            (7, 'DiscountPercent', '0', NULL),
            (8, 'Instructions', NULL, NULL),
            (9, 'PromoCode', NULL, NULL),
            (10, 'SalesOrderNumber', NULL, NULL),
            (11, 'SalesOrderStatusDesc', NULL, NULL),
            (12, 'TaxCategory', NULL, NULL),
            (13, 'TxnDate', '0001-01-01T00:00:00', NULL),
            (14, 'ShippingAddressName', NULL, NULL),
            (15, 'ShippingCity', NULL, NULL),
            (16, 'ShippingCompanyName', NULL, NULL),
            (17, 'ShippingCountry', NULL, NULL),
            (18, 'ShippingFullName', NULL, NULL),
            (19, 'ShippingPhone', NULL, NULL),
            (20, 'ShippingPhone2', NULL, NULL),
            (21, 'ShippingPhone3', NULL, NULL),
            (22, 'ShippingPhone4', NULL, NULL),
            (23, 'ShippingPostalCode', NULL, NULL),
            (24, 'ShippingState', NULL, NULL),
            (25, 'ShippingStreet', NULL, NULL),
            (26, 'ShippingStreet2', NULL, NULL),
            (27, 'BillingAddressName', NULL, NULL),
            (28, 'BillingCity', NULL, NULL),
            (29, 'BillingCompanyName', NULL, NULL),
            (30, 'BillingCountry', NULL, NULL),
            (31, 'BillingFullName', NULL, NULL),
            (32, 'BillingPhone', NULL, NULL),
            (33, 'BillingPhone2', NULL, NULL),
            (34, 'BillingPhone3', NULL, NULL),
            (35, 'BillingPhone4', NULL, NULL),
            (36, 'BillingPostalCode', NULL, NULL),
            (37, 'ShipBy', NULL, NULL),
            (38, 'Shipping', '0', NULL),
            (39, 'BillingState', NULL, NULL),
            (40, 'BillingStreet', NULL, NULL),
            (41, 'BillingStreet2', NULL, NULL),
            (42, 'RelatedCustomerID', NULL, NULL);");
 }

function courier_connector_install_services() {
  //db_query('INSERT INTO `services_endpoint` (`eid`, `name`, `server`, `path`, `authentication`, `server_settings`, `resources`, `debug`) VALUES (1, "service", "rest_server", "service", "a:0:{}\', 0x613A303A7B7D, \'a:1:{s:16:"CourierConnector";a:1:{s:10:"operations";a:3:{s:6:"create";a:1:{s:7:"enabled";s:1:"1";}s:6:"update";a:1:{s:7:"enabled";s:1:"1";}s:5:"index";a:1:{s:7:"enabled";s:1:"1";}}}}", 0);');
}

//install the quickbooks_id field and assign to all the items
function courier_connector_install_qb_id() {
  
}

function courier_connector_schema() {
  
  $schema['courier_mapping_from_category_request'] = array(
      'description' => 'Commerce (from) -> POS (To)',
      'fields' => array(
        'from_category_request_field_id' => array(
          'description' => '',
          'type' => 'serial',
          'not null' => TRUE,
        ),
        'to_category_request_field_id' => array(
          'description' => '',
          'type' => 'int',
          'not null' => TRUE,
        ),
        'from_field' => array(
          'description' => '',
          'type' => 'varchar',
          'length' => '100',
          'not null' => FALSE,
        ),
        'from_alternative' => array(
          'description' => '',
          'type' => 'varchar',
          'length' => '100',
          'not null' => FALSE,
        ),
        'sort_order' => array(
          'description' => '',
          'type' => 'int',
          'not null' => FALSE,
          'default' => 0,
        ),
        'commands' => array(
          'description' => '',
          'type' => 'varchar',
          'length' => '500',
          'not null' => FALSE,
        ),
      ),
      'primary key' => array('from_category_request_field_id'),
      'indexes' => array(
        'FK_courier_mapping_category_req' => array('to_category_request_field_id'),
      ),
    );

    $schema['courier_mapping_from_category_response'] = array(
    'description' => 'POS (from) -> Commerce (To)',
    'fields' => array(
      'from_category_response_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_category_response_field_id' => array(
        'description' => '',
        'type' => 'int',
        'not null' => TRUE,
      ),
      'from_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'from_alternative' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'sort_order' => array(
        'description' => '',
        'type' => 'int',
        'not null' => FALSE,
        'default' => 0,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('from_category_response_field_id'),
    'indexes' => array(
      'FK_courier_mapping_category_resp' => array('to_category_response_field_id'),
    ),
    );

    $schema['courier_mapping_from_customer_request'] = array(
    'description' => 'Commerce (from) -> POS (To)',
    'fields' => array(
      'from_customer_request_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_customer_request_field_id' => array(
        'description' => '',
        'type' => 'int',
        'not null' => TRUE,
      ),
      'from_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'from_alternative' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'sort_order' => array(
        'description' => '',
        'type' => 'int',
        'not null' => FALSE,
        'default' => 0,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('from_customer_request_field_id'),
    'indexes' => array(
      'FK_courier_mapping_customer_req' => array('to_customer_request_field_id'),
    ),
  );
  $schema['courier_mapping_from_customer_response'] = array(
    'description' => 'POS (from) -> Commerce (To)',
    'fields' => array(
      'from_customer_response_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_customer_response_field_id' => array(
        'description' => '',
        'type' => 'int',
        'not null' => TRUE,
      ),
      'from_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'from_alternative' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'sort_order' => array(
        'description' => '',
        'type' => 'int',
        'not null' => FALSE,
        'default' => 0,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('from_customer_response_field_id'),
    'indexes' => array(
      'FK_courier_mapping_customer_resp' => array('to_customer_response_field_id'),
    ),
  );
  $schema['courier_mapping_from_inventoryitem_request'] = array(
    'description' => 'Commerce (from) -> POS (To)',
    'fields' => array(
      'from_inventoryitem_request_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_inventoryitem_request_field_id' => array(
        'description' => '',
        'type' => 'int',
        'not null' => TRUE,
      ),
      'from_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'from_alternative' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'sort_order' => array(
        'description' => '',
        'type' => 'int',
        'not null' => FALSE,
        'default' => 0,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('from_inventoryitem_request_field_id'),
    'indexes' => array(
      'FK_courier_mapping_product_req' => array('to_inventoryitem_request_field_id'),
    ),
  );
  $schema['courier_mapping_from_inventoryitem_response'] = array(
    'description' => 'POS (from) -> Commerce (To)',
    'fields' => array(
      'from_inventoryitem_response_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_inventoryitem_response_field_id' => array(
        'description' => '',
        'type' => 'int',
        'not null' => TRUE,
      ),
      'from_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'from_alternative' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'sort_order' => array(
        'description' => '',
        'type' => 'int',
        'not null' => FALSE,
        'default' => 0,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('from_inventoryitem_response_field_id'),
    'indexes' => array(
      'FK_courier_mapping_p_resp' => array('to_inventoryitem_response_field_id'),
    ),
  );
  $schema['courier_mapping_from_iteminventory_request'] = array(
    'description' => 'Commerce (from) -> POS (To)',
    'fields' => array(
      'from_iteminventory_request_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_iteminventory_request_field_id' => array(
        'description' => '',
        'type' => 'int',
        'not null' => TRUE,
      ),
      'from_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'from_alternative' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'sort_order' => array(
        'description' => '',
        'type' => 'int',
        'not null' => FALSE,
        'default' => 0,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('from_iteminventory_request_field_id'),
    'indexes' => array(
      'FK_courier_mapping_product_req' => array('to_iteminventory_request_field_id'),
    ),
  );
  $schema['courier_mapping_from_iteminventory_response'] = array(
    'description' => 'POS (from) -> Commerce (To)',
    'fields' => array(
      'from_iteminventory_response_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_iteminventory_response_field_id' => array(
        'description' => '',
        'type' => 'int',
        'not null' => TRUE,
      ),
      'from_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'from_alternative' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'sort_order' => array(
        'description' => '',
        'type' => 'int',
        'not null' => FALSE,
        'default' => 0,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('from_iteminventory_response_field_id'),
    'indexes' => array(
      'FK_courier_mapping_p_resp' => array('to_iteminventory_response_field_id'),
    ),
  );
  $schema['courier_mapping_from_order_response'] = array(
    'description' => 'POS (from) -> Commerce (To)',
    'fields' => array(
      'from_order_response_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_order_response_field_id' => array(
        'description' => '',
        'type' => 'int',
        'not null' => TRUE,
      ),
      'from_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'from_alternative' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'sort_order' => array(
        'description' => '',
        'type' => 'int',
        'not null' => FALSE,
        'default' => 0,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('from_order_response_field_id'),
    'indexes' => array(
      'FK_courier_mapping_order_resp' => array('to_order_response_field_id'),
    ),
  );
  $schema['courier_mapping_from_payment_response'] = array(
    'description' => 'POS (from) -> Commerce (To)',
    'fields' => array(
      'from_payment_response_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_payment_response_field_id' => array(
        'description' => '',
        'type' => 'int',
        'not null' => TRUE,
      ),
      'from_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'from_alternative' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'sort_payment' => array(
        'description' => '',
        'type' => 'int',
        'not null' => FALSE,
        'default' => 0,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('from_payment_response_field_id'),
    'indexes' => array(
      'FK_courier_mapping_payment_resp' => array('to_payment_response_field_id'),
    ),
  );
  $schema['courier_mapping_from_salesorder_request'] = array(
    'description' => 'Commerce (from) -> POS (To)',
    'fields' => array(
      'from_salesorder_request_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_salesorder_request_field_id' => array(
        'description' => '',
        'type' => 'int',
        'not null' => TRUE,
      ),
      'from_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'from_alternative' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'sort_order' => array(
        'description' => '',
        'type' => 'int',
        'not null' => FALSE,
        'default' => 0,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('from_salesorder_request_field_id'),
    'indexes' => array(
      'FK_courier_mapping_salesorder_req' => array('to_salesorder_request_field_id'),
    ),
  );
  $schema['courier_mapping_from_salesorder_response'] = array(
    'description' => 'POS (from) -> Commerce (To)',
    'fields' => array(
      'from_salesorder_response_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_salesorder_response_field_id' => array(
        'description' => '',
        'type' => 'int',
        'not null' => TRUE,
      ),
      'from_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'from_alternative' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'sort_order' => array(
        'description' => '',
        'type' => 'int',
        'not null' => FALSE,
        'default' => 0,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('from_salesorder_response_field_id'),
    'indexes' => array(
      'FK_courier_mapping_order_resp' => array('to_salesorder_response_field_id'),
    ),
  );
  $schema['courier_mapping_from_salesorderitem_request'] = array(
    'description' => 'Commerce (from) -> POS (To)',
    'fields' => array(
      'from_salesorderitem_request_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_salesorderitem_request_field_id' => array(
        'description' => '',
        'type' => 'int',
        'not null' => TRUE,
      ),
      'from_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'from_alternative' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'sort_order' => array(
        'description' => '',
        'type' => 'int',
        'not null' => FALSE,
        'default' => 0,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('from_salesorderitem_request_field_id'),
    'indexes' => array(
      'FK_courier_mapping_salesorderitem_req' => array('to_salesorderitem_request_field_id'),
    ),
  );
  $schema['courier_mapping_to_category_request'] = array(
    'description' => '',
    'fields' => array(
      'to_category_request_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'default_value' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('to_category_request_field_id'),
  );
  $schema['courier_mapping_to_category_response'] = array(
    'description' => '',
    'fields' => array(
      'to_category_response_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'default_value' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('to_category_response_field_id'),
  );
  $schema['courier_mapping_to_customer_request'] = array(
    'description' => '',
    'fields' => array(
      'to_customer_request_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'default_value' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('to_customer_request_field_id'),
  );
    $schema['courier_mapping_to_customer_response'] = array(
    'description' => '',
    'fields' => array(
      'to_customer_response_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'default_value' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('to_customer_response_field_id'),
  );
  $schema['courier_mapping_to_inventoryitem_request'] = array(
    'description' => '',
    'fields' => array(
      'to_inventoryitem_request_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'default_value' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
      'active' => array(
        'description' => '',
        'type' => 'int',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('to_inventoryitem_request_field_id'),
  );
  $schema['courier_mapping_to_inventoryitem_response'] = array(
    'description' => '',
    'fields' => array(
      'to_inventoryitem_response_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'default_value' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('to_inventoryitem_response_field_id'),
  );
  $schema['courier_mapping_to_iteminventory_request'] = array(
    'description' => '',
    'fields' => array(
      'to_iteminventory_request_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'default_value' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
      'active' => array(
        'description' => '',
        'type' => 'int',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('to_iteminventory_request_field_id'),
  );
  $schema['courier_mapping_to_iteminventory_response'] = array(
    'description' => '',
    'fields' => array(
      'to_iteminventory_response_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'default_value' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('to_iteminventory_response_field_id'),
  );
  $schema['courier_mapping_to_order_response'] = array(
    'description' => '',
    'fields' => array(
      'to_order_response_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'default_value' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('to_order_response_field_id'),
  );
  $schema['courier_mapping_to_payment_response'] = array(
    'description' => '',
    'fields' => array(
      'to_payment_response_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'default_value' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('to_payment_response_field_id'),
  );
  $schema['courier_mapping_to_salesorder_request'] = array(
    'description' => '',
    'fields' => array(
      'to_salesorder_request_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'default_value' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('to_salesorder_request_field_id'),
  );
  $schema['courier_mapping_to_salesorder_response'] = array(
    'description' => '',
    'fields' => array(
      'to_salesorder_response_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'default_value' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('to_salesorder_response_field_id'),
  );
  $schema['courier_mapping_to_salesorderitem_request'] = array(
    'description' => '',
    'fields' => array(
      'to_salesorderitem_request_field_id' => array(
        'description' => '',
        'type' => 'serial',
        'not null' => TRUE,
      ),
      'to_field' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'default_value' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
      'commands' => array(
        'description' => '',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('to_salesorderitem_request_field_id'),
  );
//  $schema['courier_requests'] = array(
//    'description' => '',
//    'fields' => array(
//      'job_id' => array(
//        'description' => '',
//        'type' => 'serial',
//        'not null' => TRUE,
//      ),
//      'job_date' => array(
//        'description' => '',
//        'type' => 'timestamp',
//        'not null' => FALSE,
//        'default' => 'CURRENT_TIMESTAMP',
//      ),
//      'request_type' => array(
//        'description' => '',
//        'type' => 'varchar',
//        'length' => '50',
//        'not null' => FALSE,
//      ),
//      'request_method' => array(
//        'description' => '',
//        'type' => 'varchar',
//        'length' => '50',
//        'not null' => FALSE,
//      ),
//      'request_data' => array(
//        'description' => '',
//        'type' => 'varchar',
//        'length' => '3000',
//        'not null' => FALSE,
//      ),
//      'processed' => array(
//        'description' => '',
//        'type' => 'int',
//        'size' => 'tiny',
//        'not null' => FALSE,
//        'default' => 0,
//      ),
//      'processed_date' => array(
//        'description' => '',
//        'type' => 'timestamp',
//        'not null' => FALSE,
//      ),
//    ),
//    'primary key' => array('job_id'),
//  );
//  $schema['courier_responses'] = array(
//    'description' => '',
//    'fields' => array(
//      'response_id' => array(
//        'description' => '',
//        'type' => 'serial',
//        'not null' => TRUE,
//      ),
//      'job_id' => array(
//        'description' => '',
//        'type' => 'int',
//        'not null' => FALSE,
//      ),
//      'job_date' => array(
//        'description' => '',
//        'type' => 'timestamp',
//        'not null' => FALSE,
//        'default' => 'CURRENT_TIMESTAMP',
//      ),
//      'status' => array(
//        'description' => '',
//        'type' => 'varchar',
//        'length' => '10',
//        'not null' => FALSE,
//      ),
//      'record_count' => array(
//        'description' => '',
//        'type' => 'int',
//        'not null' => FALSE,
//      ),
//      'number_of_chunks' => array(
//        'description' => '',
//        'type' => 'int',
//        'not null' => FALSE,
//      ),
//      'chunk_number' => array(
//        'description' => '',
//        'type' => 'int',
//        'not null' => FALSE,
//      ),
//      'response_xml' => array(
//        'description' => '',
//        'type' => 'text',
//        'size' => 'big',
//        'not null' => FALSE,
//      ),
//      'processed' => array(
//        'description' => '',
//        'type' => 'int',
//        'size' => 'tiny',
//        'not null' => FALSE,
//        'default' => 0,
//      ),
//      'processed_date' => array(
//        'description' => '',
//        'type' => 'timestamp',
//        'not null' => FALSE,
//      ),
//    ),
//    'primary key' => array('response_id'),
//    'indexes' => array(
//      'job_date' => array('job_date'),
//      'job_id' => array('job_id'),
//    ),
//  );
//  $schema['courier_transaction_log'] = array(
//    'description' => '',
//    'fields' => array(
//      'transaction_id' => array(
//        'description' => '',
//        'type' => 'serial',
//        'not null' => TRUE,
//      ),
//      'trans_date' => array(
//        'description' => '',
//        'type' => 'timestamp',
//        'not null' => FALSE,
//        'default' => 'CURRENT_TIMESTAMP',
//      ),
//      'type' => array(
//        'description' => '0 = request, 1 = response, ',
//        'type' => 'int',
//        'not null' => FALSE,
//      ),
//      'message' => array(
//        'description' => '',
//        'type' => 'text',
//        'not null' => FALSE,
//      ),
//      'status' => array(
//        'description' => '',
//        'type' => 'varchar',
//        'length' => '50',
//        'not null' => FALSE,
//      ),
//    ),
//    'primary key' => array('transaction_id'),
//  );
  return $schema;
}

function courier_connector_install_manual_tables() {
  db_query("CREATE TABLE `courier_requests` (
    `job_id` INT(10) NOT NULL AUTO_INCREMENT,
    `job_date` TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP,
    `request_type` VARCHAR(50) NULL DEFAULT NULL,
    `request_method` VARCHAR(50) NULL DEFAULT NULL,
    `request_data` VARCHAR(3000) NULL DEFAULT NULL,
    `processed` TINYINT(4) NULL DEFAULT '0',
    `processed_date` DATETIME NULL DEFAULT NULL,
    PRIMARY KEY (`job_id`)
    )");

  db_query("CREATE TABLE `courier_responses` (
    `response_id` INT(11) NOT NULL AUTO_INCREMENT,
    `job_id` INT(10) NULL DEFAULT NULL,
    `job_date` TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP,
    `status` VARCHAR(10) NULL DEFAULT NULL,
    `record_count` INT(11) NULL DEFAULT NULL,
    `number_of_chunks` INT(10) NULL DEFAULT NULL,
    `chunk_number` INT(10) NULL DEFAULT NULL,
    `response_xml` LONGTEXT NULL,
    `processed` TINYINT(4) NULL DEFAULT '0',
    `processed_date` DATETIME NULL DEFAULT NULL,
    PRIMARY KEY (`response_id`),
    INDEX `job_id` (`job_id`),
    INDEX `job_date` (`job_date`)
  )");
  
  db_query("CREATE TABLE `courier_transaction_log` (
    `transaction_id` INT(10) NOT NULL AUTO_INCREMENT,
    `trans_date` TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP,
    `type` INT(10) NULL DEFAULT NULL COMMENT '0 = request, 1 = response, ',
    `message` TEXT NULL,
    `status` VARCHAR(50) NULL DEFAULT NULL,
    PRIMARY KEY (`transaction_id`)
  )");
}