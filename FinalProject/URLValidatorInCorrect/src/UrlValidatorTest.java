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

//   Partition test 1
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

// Partition test 2
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

// Partition test 3
   public void testPort()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   try{
	        assertTrue(urlVal.isValid("http://www.oregonstate.edu:80"));
	   } catch (AssertionError t){
	        System.out.println("Valid 2 digit Port test failed");
	   }

	   try{
	        assertFalse(urlVal.isValid("http://www.oregonstate.edu:-1"));
	   } catch (AssertionError t){
	        System.out.println("Invalid Port test failed");
	   }


	   try{
	        assertTrue(urlVal.isValid("http://www.oregonstate.edu:1"));
	   } catch (AssertionError t){
	        System.out.println("Valid 1 digit Port test failed");
	   }


	   try{
	        assertTrue(urlVal.isValid("http://www.oregonstate.edu:999"));
	   } catch (AssertionError t){
	        System.out.println("Valid 3 digit Port test failed");
	   }


	   try{
	        assertTrue(urlVal.isValid("http://www.oregonstate.edu:9999"));
	   } catch (AssertionError t){
	        System.out.println("Valid 4 digit Port test failed");
	   }

	   try{
	        assertTrue(urlVal.isValid("http://www.oregonstate.edu:19999"));
	   } catch (AssertionError t){
	        System.out.println("Valid 5 digit Port test failed");
	   }

   }

// Partition test 4
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


// Partition test 5
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



   public void testIsValid()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   for(int i = 0;i< protocolArr.length; i++)
	//    for(int i = 0;i< 1; i++)
	   {
		   for (int j = 0; j < domainArr.length; j++)
		//    for (int j = 0; j < 1; j++)
		   {
			   for (int k = 0; k < portArr.length; k++)
			//    for (int k = 0; k < 1; k++)
			   {
				   for (int l = 0; l < pathArr.length; l++)
				//    for (int l = 0; l < 3; l++)
				   {
					   for (int m = 0; m < queryArr.length; m++)
					//    for (int m = 0; m < 1; m++)
					   {
						   String url = protocolArr[i].item+domainArr[j].item+portArr[k].item+pathArr[l].item+queryArr[m].item;
						   if (protocolArr[i].valid && domainArr[j].valid && portArr[k].valid && pathArr[l].valid && queryArr[m].valid)
						   {
							   try {
								   assertTrue(urlVal.isValid(url));
							   } catch(AssertionError e) {
								   System.out.println("True Assertion on "+url+" failed.");
							   }
						   } else {
							   try {
								   assertFalse(urlVal.isValid(url));
							   } catch(AssertionError e) {
								   System.out.println("False Assertion on "+url+" failed.");
							   }
						   }
					   }
				   }
			   }
		   }
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

   ResultPair[] protocolArr = {new ResultPair("http://", true),
           new ResultPair("ftp://", true),
           new ResultPair("h3t://", true),
           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
           new ResultPair("://", false),
           new ResultPair("", true)};

   ResultPair[] domainArr = {new ResultPair("www.google.com", true),
              new ResultPair("go.com", true),
              new ResultPair("go.au", true),
              new ResultPair("0.0.0.0", true),
              new ResultPair("255.255.255.255", true),
              new ResultPair("256.256.256.256", false),
              new ResultPair("255.com", true),
              new ResultPair("1.2.3.4.5", false),
              new ResultPair("1.2.3.4.", false),
              new ResultPair("1.2.3", false),
              new ResultPair(".1.2.3.4", false),
              new ResultPair("go.a", false),
              new ResultPair("go.a1a", false),
              new ResultPair("go.cc", true),
              new ResultPair("go.1aa", false),
              new ResultPair("aaa.", false),
              new ResultPair(".aaa", false),
              new ResultPair("aaa", false),
              new ResultPair("", false)
   };
   ResultPair[] portArr = {new ResultPair(":80", true),
		   	new ResultPair(":65535", true),
		   	new ResultPair(":0", true),
		   	new ResultPair("", true),
		   	new ResultPair(":-1", false),
		   	new ResultPair(":65636", true),
		   	new ResultPair(":65a", false)
   };

   ResultPair[] pathArr = {new ResultPair("/test1", true),
                new ResultPair("/t123", true),
                new ResultPair("/$23", true),
                new ResultPair("/..", false),
                new ResultPair("/../", false),
                new ResultPair("/test1/", true),
                new ResultPair("/#", false),
                new ResultPair("", true),
                new ResultPair("/test1/file", true),
                new ResultPair("/t123/file", true),
                new ResultPair("/$23/file", true),
                new ResultPair("/../file", false),
                new ResultPair("/..//file", false),
                new ResultPair("/test1//file", true),
                new ResultPair("/#/file", false)
   };

   ResultPair[] queryArr = {new ResultPair("?action=view", true),
          new ResultPair("?action=edit&mode=up", true),
          new ResultPair("", true)
   };
}
