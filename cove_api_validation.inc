<?php
/**
 * Validate individual arguments to be sent to a COVE API Request.
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
    // franchises method
    'franchises' => array(
      'slug' => 'string',
      'page' => 'int',
      'sort' => 'string',
    ),
    // shows method
    'shows' => array(
      'audience_scope' => 'string',
      'audience' => 'string',
      'franchise-slug' => 'string',
      'franchise-id' => 'string',
      'genre-id' => 'string',
      'genre-slug' => 'string',
      'page' => 'int',
      'sort' => 'string',
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
      return FALSE;
  }

}
