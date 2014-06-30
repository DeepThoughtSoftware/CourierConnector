<?php

class CourierXMLResponseParser implements ServicesParserInterface {
  public function parse(ServicesContextInterface $context) {
    return $context->getRequestBody();    
  }
}