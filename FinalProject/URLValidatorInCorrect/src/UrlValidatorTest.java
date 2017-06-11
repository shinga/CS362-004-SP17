/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ErrorCollector;
import junit.framework.TestCase;
import java.util.regex.Matcher;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {
   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);

   }

   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   try{
	        assertFalse(urlVal.isValid("http://///www.amazon.com"));
	   } catch (AssertionError t){
	        System.out.println("http://///www.amazon.com test failed");
	   }
	   try{
	        assertTrue(urlVal.isValid("http://www.amazon.com"));
	   } catch (AssertionError t){
	        System.out.println("http://www.amazon.com test failed");
	   }
	   try{
	        assertFalse(urlVal.isValid("http:///////www.google.com/"));
	   } catch (AssertionError t){
	        System.out.println("http://///www.google.com test failed");
	   }
	   try{
	        assertTrue(urlVal.isValid("http://www.google.com/"));
	   } catch (AssertionError t){
	        System.out.println("http://www.google.com test failed");
	   }
	   try{
	        assertTrue(urlVal.isValid("www.google.com"));
	   } catch (AssertionError t){
	        System.out.println("www.google.com test failed");
	   }
	   try{
	        assertFalse(urlVal.isValid("http://google.com//someweirdpath"));
	   } catch (AssertionError t){
	        System.out.println("http://google.com//someweirdpath test failed");
	   }
	   try{
	        assertFalse(urlVal.isValid("http://www.google.com:-1"));
	   } catch (AssertionError t){
	        System.out.println("http://www.google.com:-1 test failed");
	   }

	   try{
	        assertTrue(urlVal.isValid("http://www.google.com:0/test?action=view"));
	   } catch (AssertionError t){
	        System.out.println("http://www.google.com:0/test?action=view test failed");
	   }


	   
   }
   
   
   public void testProtocol()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	  
	   
	   try{
	        assertTrue(urlVal.isValid("http://www.oregonstate.edu"));
	   } catch (AssertionError t){
	        System.out.println("Valid Authority test partition failed");
	   }
	   
	   try{
	        assertFalse(urlVal.isValid("http//www.oregonstate.edu"));
	   } catch (AssertionError t){
	        System.out.println("Invalid Authority test partition failed");
	   }
	   
	   
   }

   public void testDomain()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   try{
	        assertTrue(urlVal.isValid("http://www.oregonstate.edu"));
	   } catch (AssertionError t){
	        System.out.println("Valid Domain test failed");
	   }
	   
	   try{
	        assertFalse(urlVal.isValid("http://jjiorewafli"));
	   } catch (AssertionError t){
	        System.out.println("Invalid Domain test failed");
	   }
   }
   

   public void testPort()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   try{
	        assertTrue(urlVal.isValid("http://www.oregonstate.edu:80"));
	   } catch (AssertionError t){
	        System.out.println("Valid Port test failed");
	   }
	   
	   try{
	        assertFalse(urlVal.isValid("http://www.oregonstate.edu:-13"));
	   } catch (AssertionError t){
	        System.out.println("Invalid Port test failed");
	   }
	   
   }
   

   public void testPath()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   try{
	        assertTrue(urlVal.isValid("http://www.oregonstate.edu/test"));
	   } catch (AssertionError t){
	        System.out.println("Valid Path test failed");
	   }
	   
	   try{
	        assertFalse(urlVal.isValid("http://www.oregonstate.edu/.."));
	   } catch (AssertionError t){
	        System.out.println("Invalid Path test failed");
	   }
	   
   }
	   
   

   public void testQuery()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   try{
	        assertTrue(urlVal.isValid("http://www.oregonstate.edu?action=view"));
	   } catch (AssertionError t){
	        System.out.println("Valid Query test failed");
	   }
	   
	   try{
	        assertFalse(urlVal.isValid("http://www.oregonstate.edu????lol"));
	   } catch (AssertionError t){
	        System.out.println("Invalid Query test failed");
	   }
	   
   }
	   
	   
	   
	   
	   
	
   
   public void testYourSecondPartition(){
	   
   }
   
   
   public void testIsValid()
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
