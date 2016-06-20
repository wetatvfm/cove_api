<?php
/**
 * Validate inidividual arguments to be sent to a COVE API Request.
 *
 * @param string $key
 *   The filter or option.
 *
 * @param string $value
 *   The value of the filter or option.
 *
 * @param string $method
 *   The method being called.
 *
 * @return bool
 *   TRUE if the filter or option if it is valid.
 */
function _cove_api_allowed_values($key, $value, $method) {

  // set up arrays to handle most of the cases
  $patterns = array (
    // videos method
    'videos' => array(
      // filters
      'filter_guid' => 'string',
      'filter_title'=> 'string',
      'filter_program' => 'int',
      'filter_program_title' => 'string',
      'filter_nola_root' => 'string',
      'filter_program__nola_root' => 'string',
      'filter_record_last_updated_datetime__gt' => '_cove_api_simple_date_check',
      'filter_type' => 'string',
      'exclude_type' => 'string',
      'filter_tp_media_object_id' => 'int',
      'filter_mediafile_set__video_encoding__mime_type' => 'string',
      'content_region' => 'string',
      'audience' => 'string',
      'filter_availability_status' => 'string',

      // advanced filters
      'filter_expire_datetime__gt' => '_cove_api_simple_date_check',
      'filter_expire_datetime__lt' => '_cove_api_simple_date_check',
      'filter_available_datetime__gt' => '_cove_api_simple_date_check',
      'filter_available_datetime__lt' => '_cove_api_simple_date_check',
      'exclude_mediafile_set_\_video_encoding__mime_type' => 'string',
      'filter_producer__name' => 'string',
      'exclude_producer__name' => 'string',

      // modifiers
      'order_by' => 'string',
      'fields' => 'string',
      'limit_start' => 'int',
      'limit_stop'  => 'int',
    ),


    // programs method
    'programs' => array(
      // filters
      'filter_nola_root' => 'string',
      'filter_title' => 'string',
      'filter_producer__name' => 'string',

      // modifiers
      'order_by' => 'string',
      'fields' => 'string',
      'limit_start' => 'int',
      'limit_stop'  => 'int',
    ),

    // categories method
    'categories' => array(
      //filters
      'filter_namespace__name' => 'string',
      'filter_id' => 'int',
      'filter_parent__name' => 'string',
      'filter_name' => 'string',
      'filter_program' => 'int',
      'filter_video' => 'int',

      //modifiers
      'order_by' => 'string',
      'limit_start' => 'int',
    ),

    // graveyard method
    'graveyard' => array(
      'deleted_since' => '_cove_api_full_date_check',
      'limit_start' => 'int',
    ),

  );

  if (!isset($patterns[$method][$key])) {
    return FALSE;
  }

  switch ($patterns[$method][$key]) {
    case 'int':
      return is_numeric($value);
      break;
    case 'string':
      return is_string($value);
      break;
    default:
      if(is_callable($patterns[$method][$key])){
        return $patterns[$method][$key]($value);
      }
      else {
        return FALSE;
      }
  }

}

/**
 * Validate date to be sent to a COVE API Request. It should be in
 * YYYY-MM-DD format.
 *
 * @param string $value
 *   The value of the filter or option.
 *
 * @return bool
 *   True if the filter or option is valid.
 */
function _cove_api_simple_date_check($value) {

  // check to see if value is in yyyy-mm-dd format
  $dt = DateTime::createFromFormat("Y-m-d", $value);
  if ($dt !== false && !array_sum($dt->getLastErrors())) {
    return TRUE;
  }
  else {
   watchdog(
    'cove_api',
    'Validation error. %key expects a date formatted as YYYY-MM-DD.',
    array(
      '%key' => $key
    ), WATCHDOG_ERROR);
  }
}

/**
 * Validate date to be sent to a COVE API Request. It should be in
 * YYYY-MM-DDTHH:MM:SS format.
 *
 * @param string $value
 *   The value of the filter or option.
 *
 * @return bool
 *   True if the filter or option is valid.
 */

function _cove_api_full_date_check($value) {

  // check to see if value is in yyyy-mm-ddThh:mm:ss format
  $dt = DateTime::createFromFormat('Y-m-d\TH:i:s', $value);
  if ($dt !== false && !array_sum($dt->getLastErrors())) {
    return TRUE;
  }
  else {
   watchdog(
    'cove_api',
    'Validation error. %key expects a date formatted as YYYY-MM-DDTHH:MM:SS.',
    array(
      '%key' => $key
    ), WATCHDOG_ERROR);
  }
}
